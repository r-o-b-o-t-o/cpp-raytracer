#include "scene/SceneObj.hpp"
#include "scene/Plane.hpp"
#include "scene/Square.hpp"
#include "scene/Cube.hpp"
#include "scene/Sphere.hpp"

namespace Scene {
    SceneObj::SceneObj() : camera(Scene::Camera(Math::Point())) {

    }

    SceneObj::SceneObj(YAML::Node root) : camera(root["camera"].as<Math::Point>()) {
        this->insertLight(Scene::Light(root["light"].as<Math::Point>()));

        YAML::Node objects = root["objects"];
        for (YAML::const_iterator it = objects.begin(); it != objects.end(); ++it) {
            std::string objName = it->first.as<std::string>();
            std::string type = objects[objName]["type"].as<std::string>();
            this->insertObj(nodeToObj(type, objects[objName]));
        }
    }

    SceneObj::~SceneObj() {
        for (auto &obj : this->objs) {
            delete obj;
        }
        this->objs.clear();
    }

    Scene::Light SceneObj::getLight(int i) {
        return this->lights[i];
    }

    std::vector<Scene::Light> SceneObj::getAllLights() {
        return this->lights;
    }

    void SceneObj::insertLight(Scene::Light l) {
        this->lights.push_back(l);
    }

    Scene::Object* SceneObj::getObj(int i) {
        return this->objs[i];
    }

    std::vector<Object*> &SceneObj::getAllObj() {
        return this->objs;
    }

    void SceneObj::insertObj(Object* obj) {
        this->objs.push_back(obj);
    }

    cv::Mat SceneObj::createColorsMat(int height, int width) {
        cv::Mat mat(height, width, CV_8UC4);

        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.cols; ++j) {
                auto &bgra = mat.at<cv::Vec4b>(i, j);
                // x val [0, 1]
                float x = (float)i / (float)mat.rows;
                // y val [0, 1]
                float y = (float)j / (float)mat.cols;

                Math::Ray ray = this->camera.getRay(x, y);
                for (auto &obj : this->objs) {
                    Math::Point impact;
                    if (obj->intersect(ray, impact)) {
                        //Get color here
                        bgra[0] = cv::saturate_cast<uchar>(0.0f);
                        bgra[1] = cv::saturate_cast<uchar>(128.0f);
                        bgra[2] = cv::saturate_cast<uchar>(0.0f);
                        bgra[3] = cv::saturate_cast<uchar>(255.0f);
                    } else {
                        bgra[0] = cv::saturate_cast<uchar>(0.0f);
                        bgra[1] = cv::saturate_cast<uchar>(0.0f);
                        bgra[2] = cv::saturate_cast<uchar>(0.0f);
                        bgra[3] = cv::saturate_cast<uchar>(255.0f);
                    }
                }
            }
        }

        return mat;
    }

    void SceneObj::exportImage(int height, int width) {
        std::cout << "Exporting image..." << std::endl;

        auto mat = this->createColorsMat(height, width);

        std::vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(9);

        try {
            imwrite("alpha.png", mat, compression_params);
        } catch (std::runtime_error &ex) {
            std::cerr << "Exception converting image to PNG format: " << ex.what() << std::endl;
            return;
        }
        std::cout << "Saved PNG file with alpha data." << std::endl;
    }

    Scene::Object* SceneObj::nodeToObj(const std::string &type, const YAML::Node &obj) {
        Math::Point p(obj.as<Math::Point>());

        if (type == "plane") return new Scene::Plane(p);
        if (type == "square") return new Scene::Square(p);
        if (type == "cube") return new Scene::Cube(p);
        if (type == "sphere") return new Scene::Sphere(p);

        return nullptr;
    }

    const Camera &SceneObj::getCamera() const {
        return camera;
    }

    void SceneObj::setCamera(const Camera &camera) {
        SceneObj::camera = camera;
    }
}