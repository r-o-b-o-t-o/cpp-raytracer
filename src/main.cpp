#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include "scene/Entity.hpp"
#include "scene/Camera.hpp"
#include "scene/Light.hpp"
#include "scene/Object.hpp"
#include "scene/Plane.hpp"

void createAlphaMat(cv::Mat &mat) {
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            auto &rgba = mat.at<cv::Vec4b>(i, j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = cv::saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) * UCHAR_MAX);
            rgba[2] = cv::saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) * UCHAR_MAX);
            rgba[3] = cv::saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
        }
    }
}

void exportImage(int height, int width) {
    // Create mat with alpha channel
    cv::Mat mat(height, width, CV_8UC4);
    createAlphaMat(mat);

    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);

    try {
        imwrite("alpha.png", mat, compression_params);
    }
    catch (std::runtime_error &ex) {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
        return;
    }
    fprintf(stdout, "Saved PNG file with alpha data.\n");
}

Math::Point nodeToPoint(YAML::Node obj) {
    float x = obj["x"].as<float>();
    float y = obj["y"].as<float>();
    float z = obj["z"].as<float>();
    return Math::Point(x, y, z);
}

Scene::Object* nodeToObj(YAML::Node obj){
    std::string type = obj["type"].as<std::string>();
    if (type == "plane"){
        return new Scene::Plane(nodeToPoint(obj));
    }
    if (type == "quad"){
        return new Scene::Plane(nodeToPoint(obj));
    }
    if (type == "cube"){
        return new Scene::Plane(nodeToPoint(obj));
    }
    if (type == "sphere"){
        return new Scene::Plane(nodeToPoint(obj));
    }
    else {
        return nullptr;
    }
}

void loadScene(YAML::Node root, std::multimap<std::string, Scene::Entity*> objs) {
    Scene::Camera* camera = new Scene::Camera(nodeToPoint(root["camera"]));
    Scene::Light* light = new Scene::Light(nodeToPoint(root["light"]));

    objs.insert(std::make_pair("camera", camera));
    objs.insert(std::make_pair("light", light));

    YAML::Node objects = root["objects"];
    for(YAML::const_iterator it=objects.begin();it!=objects.end();++it) {
        std::string objName = it->first.as<std::string>();
        objs.insert(std::make_pair("objects", nodeToObj(objects[objName])));
    }
}

void useScene(const std::string &scene) {
    YAML::Node config = YAML::LoadFile(scene);
    std::string sceneName = config["name"].as<std::string>();
    std::cout << "Using scene: " << sceneName << std::endl;

    std::multimap<std::string, Scene::Entity*> objs;

    loadScene(config, objs);

    YAML::Node resolution = config["resolution"];
    exportImage(resolution["height"].as<int>(), resolution["width"].as<int>());

    for (auto it = objs.begin(); it != objs.end(); ++it) {
        delete it->second;
    }
    objs.clear();
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
