#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>
#include "scene/Entity.hpp"
#include "scene/Camera.hpp"
#include "scene/Light.hpp"
#include "math/Point.hpp"

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

Math::Point nodeToPoint(YAML::Node obj){
    float x = obj["x"].as<float>();
    float y = obj["y"].as<float>();
    float z = obj["z"].as<float>();
    return Math::Point(x, y, z);
}

void loadScene(YAML::Node root, std::vector<Scene::Entity> objs){
    Scene::Camera camera(nodeToPoint(root["camera"]));
    Scene::Light light(nodeToPoint(root["light"]));

    objs.push_back(camera);
    objs.push_back(light);
}

void useScene(const std::string &scene) {
    YAML::Node config = YAML::LoadFile(scene);
    std::string sceneName = config["name"].as<std::string>();
    std::cout << "Using scene: " << sceneName << std::endl;

    std::vector<Scene::Entity> objs;

    loadScene(config, objs);


    YAML::Node resolution = config["resolution"];
    exportImage(resolution["height"].as<int>(), resolution["width"].as<int>());
}

int main(int argv, char** argc) {
    std::vector<std::string> scenes;
    std::string path = "../scenes/";
    for (auto& entry : boost::filesystem::directory_iterator(path)) {
        scenes.push_back(entry.path().string());
    }

    std::cout << "Choose a scene:\n" << std::endl;
    int i = 1;
    for (auto &scene : scenes) {
        std::string name = YAML::LoadFile(scene)["name"].as<std::string>();
        std::cout << i << ") " <<  name << std::endl;
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
