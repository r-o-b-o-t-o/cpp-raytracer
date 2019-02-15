#include <iostream>
#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>

#include "scene/Scene.hpp"

void useScene(const std::string &scene) {
    YAML::Node config = YAML::LoadFile(scene);
    std::string sceneName = config["name"].as<std::string>();
    std::cout << "Using scene: " << sceneName << std::endl;

    scene::Scene sceneObj(config);

    YAML::Node resolution = config["resolution"];
    sceneObj.exportImage(resolution["height"].as<int>(), resolution["width"].as<int>());
}

int main(int argv, char** argc) {
    std::vector<std::string> scenes;
    std::string path = "../scenes/";
    for (auto &entry : boost::filesystem::directory_iterator(path)) {
        scenes.push_back(entry.path().string());
    }

    std::cout << "Choose a scene:\n" << std::endl;
    int i = 1;
    for (auto &scene : scenes) {
        std::string name = YAML::LoadFile(scene)["name"].as<std::string>();
        std::cout << i << ") " << name << std::endl;
        ++i;
    }

    int choice;
    std::cout << std::endl << "Your choice: ";
    std::cin >> choice;

    if (choice <= 0 || choice > scenes.size()) {
        std::cout << "Exiting..." << std::endl;
    } else {
        useScene(scenes[choice - 1]);
    }
    return 0;
}
