#include <iostream>
#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include "tinyfiledialogs.h"

#include "scene/Scene.hpp"

void getScenesList(std::vector<scene::Scene*> &scenes) {
    std::string path = "../scenes/";
    for (auto &scene : scenes) {
        delete scene;
    }
    scenes.clear();
    for (auto &entry : boost::filesystem::directory_iterator(path)) {
        scene::Scene* scene = new scene::Scene(YAML::LoadFile(entry.path().string()));
        scenes.push_back(scene);
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

        //////// Scenes Manager
        ImGui::Begin("Scenes Manager");
        ImGui::BeginChild("Left pane", ImVec2(250, 0), true);
        ImGui::BeginChild("List container", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()));
        static int selectedSceneIdx = -1;
        static scene::Scene* selectedScene = nullptr;
        {
            if (ImGui::ListBox("", &selectedSceneIdx, scenesGetter, (void*)&scenes, static_cast<int>(scenes.size()), 6)) {
                selectedScene = scenes[selectedSceneIdx];
            }
        }
        ImGui::EndChild(); // End List container
        if (ImGui::Button("Refresh")) {
            selectedSceneIdx = -1;
            selectedScene = nullptr;
            renderedScene = nullptr;
            getScenesList(scenes);
        }
        ImGui::EndChild(); // End Left pane
        ImGui::SameLine();

        ImGui::BeginGroup(); // Right pane
        if (selectedScene != nullptr) {
            ImGui::BeginChild("Container", ImVec2(0.0f, 0.0f), true);
            ImGui::BeginChild("Item view", ImVec2(0.0f, -ImGui::GetItemsLineHeightWithSpacing()));
            ImGui::Text("%s", selectedScene->getName().c_str());
            ImGui::Separator();
            ImGui::Text("%d x %d", (int)selectedScene->getCamera().getWidth(), (int)selectedScene->getCamera().getHeight());
            ImGui::Text("%d lights", (int)selectedScene->getAllLights().size());
            ImGui::Text("%d objects", (int)selectedScene->getAllObj().size());
            ImGui::EndChild(); // End Item view
            if (ImGui::Button("Render") && (renderThreadDone || mat == nullptr)) {
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
            if (ImGui::Button("Edit")) {

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
