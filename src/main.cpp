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
#include "scene/Square.hpp"
#include "scene/Cube.hpp"
#include "scene/Sphere.hpp"
#include "scene/SceneObj.hpp"


void createAlphaMat(cv::Mat &mat, Scene::SceneObj &scene) {
    Scene::Camera camera = scene.getCamera();
    Scene::Light light = scene.getLight(0);

    std::vector<Scene::Object*> objs = scene.getAllObj();

    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            auto &rgba = mat.at<cv::Vec4b>(i, j);
            // x val [0, 1]
            float x = (float)i / (float) mat.rows;
            // y val [0, 1]
            float y = (float)j / (float) mat.cols;

            //std::cout << "test: " << i << ";" << j << std::endl;
            Math::Ray ray = camera.getRay(x, y);
            //std::cout << "x;y: " << i << ";" << j << std::endl;
            for (auto it= objs.begin(); it!= objs.end(); ++it)
            {
                //Scene::Object* obj = *it;
                Math::Point impact;
                if ((*it)->intersect(ray, impact))
                {
                    //Get color here
                    //rgba[0] =
                    //rgba[1] =
                    //rgba[2] =
                    std::cout << "impact:" << i << ", " << j << std::endl;
                    rgba[0] = cv::saturate_cast<uchar>(0.0f);
                    rgba[1] = cv::saturate_cast<uchar>(128.0f);
                    rgba[2] = cv::saturate_cast<uchar>(0.0f);
                    rgba[3] = cv::saturate_cast<uchar>(255.0f);
                    
                }else {
                    rgba[0] = UCHAR_MAX;
                    rgba[1] = UCHAR_MAX;
                    rgba[2] = UCHAR_MAX;
                    rgba[3] = UCHAR_MAX;
                }
            }

        }
    }
}

void exportImage(int height, int width, Scene::SceneObj &scene) {
    // Create mat with alpha channel
    std::cout << "exporting Image" << std::endl;
    cv::Mat mat(height, width, CV_8UC4);
    createAlphaMat(mat, scene);

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

Scene::Object* nodeToObj(std::string type, YAML::Node obj){
    if (type == "plane"){
        return new Scene::Plane(nodeToPoint(obj));
    }
    if (type == "square"){
        return new Scene::Square(nodeToPoint(obj));
    }
    if (type == "cube"){
        return new Scene::Cube(nodeToPoint(obj));
    }
    if (type == "sphere"){
        return new Scene::Sphere(nodeToPoint(obj));
    }
    else {
        return nullptr;
    }
}

void loadScene(YAML::Node root, Scene::SceneObj &scene) {
    //Scene::Camera* camera = new Scene::Camera(nodeToPoint(root["camera"]));
    //Scene::Light* light = new Scene::Light(nodeToPoint(root["light"]));

    scene.setCamera(Scene::Camera(nodeToPoint(root["camera"])));
    scene.insertLight(Scene::Light(nodeToPoint(root["light"])));
    //entities.insert(std::make_pair("camera", camera));
    //entities.insert(std::make_pair("light", light));

    YAML::Node objects = root["objects"];
    for(YAML::const_iterator it=objects.begin();it!=objects.end();++it) {
        std::string objName = it->first.as<std::string>();
        std::string type = objects[objName]["type"].as<std::string>();
        scene.insertObj(nodeToObj(type, objects[objName]));
        //objs.insert(std::make_pair(type, nodeToObj(type, objects[objName])));
    }
}

void useScene(const std::string &scene) {
    YAML::Node config = YAML::LoadFile(scene);
    std::string sceneName = config["name"].as<std::string>();
    std::cout << "Using scene: " << sceneName << std::endl;

    //std::multimap<std::string, Scene::Entity*> entities;
    //std::multimap<std::string, Scene::Object*> objs;
    Scene::SceneObj sceneObj;

    loadScene(config, sceneObj);

    YAML::Node resolution = config["resolution"];
    exportImage(resolution["height"].as<int>(), resolution["width"].as<int>(), sceneObj);

    for (auto it = sceneObj.getAllObj().begin(); it != sceneObj.getAllObj().end(); ++it) {
        delete *it;
    }
    sceneObj.getAllObj().clear();
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
