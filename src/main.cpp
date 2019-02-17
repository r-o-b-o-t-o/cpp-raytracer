#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include "tinyfiledialogs.h"

#include "scene/Scene.hpp"

scene::Scene* parseSceneFromFile(const std::string &path) {
    try {
        return new scene::Scene(YAML::LoadFile(path));
    } catch (const std::exception &e) {
        std::string msg = "An error occurred while parsing \"";
        msg.append(path);
        msg.append("\":\r\n");
        msg.append(e.what());
        tinyfd_messageBox("Error", msg.c_str(), "ok", "error", 1);
    }
    return nullptr;
}

void getScenesList(std::vector<scene::Scene*> &scenes) {
    std::string path = "../scenes/";
    for (auto &scene : scenes) {
        delete scene;
    }
    scenes.clear();
    for (auto &entry : boost::filesystem::directory_iterator(path)) {
        auto scene = parseSceneFromFile(entry.path().string());
        if (scene != nullptr) {
            scene->path = boost::filesystem::canonical(entry.path()).generic_string();
            scenes.push_back(scene);
        }
    }
}

inline bool ends_with(std::string const &value, std::string const &ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void exportPng(const scene::Scene &scene, cv::Mat* mat) {
    std::string imgName = scene.getName();
    imgName.append(".png");

    char const* filterPatterns[1] = { "*.png" };
    char const* fileName = tinyfd_saveFileDialog("Save image as...", imgName.c_str(), 1, filterPatterns, nullptr);

    if (fileName) {
        std::vector<int> compressionParams;
        compressionParams.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compressionParams.push_back(9);

        auto lower = std::string(fileName);
        std::string path = std::string(fileName);
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        if (!ends_with(lower, ".png")) {
            path.append(".png");
        };

        cv::imwrite(path, *mat, compressionParams);
    }
}

scene::Scene* importYamlDialog(std::string &path) {
    char const* filterPatterns[2] = { "*.yaml", "*.yml" };
    char const* fileName = tinyfd_openFileDialog("Load scene from...", "", 2, filterPatterns, nullptr, false);

    if (fileName) {
        path = fileName;
        return parseSceneFromFile(path);
    }
    return nullptr;
}

void importYaml(std::vector<scene::Scene*> &scenes) {
    std::string p;
    auto imported = importYamlDialog(p);
    if (imported != nullptr) {
        boost::filesystem::path path(p);
        std::string dest = "../scenes/";
        dest.append(path.filename().string());
        if (boost::filesystem::equivalent(path, dest)) {
            return;
        }
        if (boost::filesystem::exists(dest)) {
            int res = tinyfd_messageBox("Overwrite file?", "This file already exists in the scenes directory.\r\nDo you want to replace it?", "yesno", "question", 1);
            if (res == 0) {
                return;
            }
        }
        imported->path = boost::filesystem::weakly_canonical(dest).generic_string();
        boost::filesystem::copy_file(path, dest, boost::filesystem::copy_option::overwrite_if_exists);
        for (auto it = scenes.begin(); it != scenes.end();) {
            auto existingScene = *it;
            if (existingScene->path == imported->path) {
                it = scenes.erase(it);
                delete existingScene;
            } else {
                ++it;
            }
        }
        scenes.push_back(imported);
    }
}

int main(int argv, char** argc) {
    std::vector<scene::Scene*> scenes;
    getScenesList(scenes);
    auto scenesGetter = [](void* data, int n, const char** out) -> bool {
        const std::vector<scene::Scene*>* v = (std::vector<scene::Scene*>*)data;
        *out = v->at(static_cast<unsigned long long int>(n))->getName().c_str();
        return true;
    };

    sf::Image image;
    sf::Texture texture;
    cv::Mat* mat = nullptr;
    std::thread renderThread;
    std::atomic<bool> renderThreadDone {false};
    std::promise<std::string> renderTimePromise;
    std::future<std::string> renderTimeFuture;
    std::string renderTime;
    bool renderWindowOpened = false;
    scene::Scene* renderedScene = nullptr;
    auto refreshTexture = [&]() {
        cv::Mat matRgb;
        cv::cvtColor(*mat, matRgb, cv::COLOR_BGRA2RGBA);
        image.create(static_cast<unsigned int>(matRgb.cols), static_cast<unsigned int>(matRgb.rows), matRgb.ptr());
        texture.loadFromImage(image);
    };

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Raytracing", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor(0, 0, 0);

    window.resetGLStates();
    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event {};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        bool isCurrentlyRendering = !(renderThreadDone || mat == nullptr);

        //////// Scenes Manager
        ImGui::Begin("Scenes Manager");
        if (ImGui::GetWindowSize().y < 100.0f) {
            ImGui::SetWindowSize(ImVec2(500.0f, 325.0f), true);
        }
        ImGui::BeginChild("Left pane", ImVec2(250, 0), true);
        ImGui::BeginChild("List container", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()));
        static int selectedSceneIdx = -1;
        static scene::Scene* selectedScene = nullptr;
        {
            ImGui::Text("Found scenes:");
            ImGui::PushItemWidth(-1.0f);
            auto numScenes = static_cast<int>(scenes.size());
            if (ImGui::ListBox("##ListScenes", &selectedSceneIdx, scenesGetter, (void*)&scenes, numScenes, numScenes)) {
                selectedScene = scenes[selectedSceneIdx];
            }
            ImGui::PopItemWidth();
        }
        ImGui::EndChild(); // End List container
        if (isCurrentlyRendering) {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
        }
        if (ImGui::Button("Refresh") && !isCurrentlyRendering) {
            selectedSceneIdx = -1;
            selectedScene = nullptr;
            renderedScene = nullptr;
            getScenesList(scenes);
        }
        if (isCurrentlyRendering) {
            ImGui::PopStyleVar();
        }
        ImGui::SameLine();
        if (ImGui::Button("Import Scene")) {
            selectedSceneIdx = -1;
            selectedScene = nullptr;
            importYaml(scenes);
        }
        ImGui::EndChild(); // End Left pane
        ImGui::SameLine();

        ImGui::BeginGroup(); // Right pane
        if (selectedScene != nullptr) {
            ImGui::BeginChild("Container", ImVec2(0.0f, 0.0f), true);
            ImGui::BeginChild("Item view", ImVec2(0.0f, -ImGui::GetItemsLineHeightWithSpacing()));
            ImGui::Text("%s", selectedScene->getName().c_str());
            ImGui::Separator();
            ImGui::TextWrapped("Path: %s", selectedScene->path.c_str());
            ImGui::NewLine();
            ImGui::Text("%d x %d", (int)selectedScene->getCamera().getWidth(), (int)selectedScene->getCamera().getHeight());
            ImGui::Text("%d lights", (int)selectedScene->getAllLights().size());
            ImGui::Text("%d objects", (int)selectedScene->getAllObj().size());
            ImGui::EndChild(); // End Item view
            if (isCurrentlyRendering) {
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }
            if (ImGui::Button("Render") && !isCurrentlyRendering) {
                delete mat;

                renderedScene = selectedScene;
                auto w = renderedScene->getCamera().getWidth();
                auto h = renderedScene->getCamera().getHeight();

                mat = new cv::Mat((int)h, (int)w, CV_8UC4);
                renderThreadDone.store(false);
                renderTimeFuture = renderTimePromise.get_future();
                renderThread = renderedScene->render(mat, std::move(renderTimePromise), renderThreadDone);

                if (!renderWindowOpened) {
                    ImGui::SetNextWindowPos(ImVec2(window.getSize().x - w - 24.0f, 8.0f), true);
                    ImGui::SetNextWindowFocus();
                }

                renderWindowOpened = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reload") && !isCurrentlyRendering) {
                bool remove = false;
                if (boost::filesystem::exists(selectedScene->path)) {
                    auto path = selectedScene->path;
                    auto newScene = parseSceneFromFile(path);
                    if (newScene != nullptr) {
                        newScene->path = path;
                        scenes[selectedSceneIdx] = newScene;
                        delete selectedScene;
                        selectedScene = newScene;
                    } else {
                        remove = true;
                    }
                } else {
                    remove = tinyfd_messageBox("Remove dangling scene?", "This file does not exist anymore.\r\nDo you want to remove the scene from the list?", "yesno", "question", 1) != 0;
                }
                if (remove) {
                    scenes.erase(scenes.begin() + selectedSceneIdx);
                    delete selectedScene;
                    selectedScene = nullptr;
                    selectedSceneIdx = -1;
                }
            }
            if (isCurrentlyRendering) {
                ImGui::PopStyleVar();
            }
            ImGui::EndChild(); // End Container
        }
        ImGui::EndGroup(); // End Right pane
        ImGui::End(); // End Scenes Manager
        ////////


        //////// Render Window
        if (renderWindowOpened && renderedScene != nullptr) {
            ImGui::Begin("Render", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
            if (!renderThreadDone) {
                refreshTexture();
            }
            ImGui::Image(texture);
            if (renderThreadDone) {
                ImGui::Text("%s", renderTime.c_str());
                if (ImGui::Button("Export as PNG")) {
                    exportPng(*renderedScene, mat);
                }
            }
            ImGui::End(); // End Render
        }
        ////////

        window.clear(bgColor);
        ImGui::SFML::Render(window);
        window.display();

        if (renderThreadDone && renderThread.joinable()) {
            refreshTexture();
            renderThread.join();
            renderTime = renderTimeFuture.get();
            renderTimePromise = std::promise<std::string>();
        }
    }

    ImGui::SFML::Shutdown();

    for (auto &scene : scenes) {
        delete scene;
    }
    scenes.clear();
    delete mat;

    return 0;
}
