#include "scene/Scene.hpp"
#include "scene/Plane.hpp"
#include "scene/Square.hpp"
#include "scene/Cube.hpp"
#include "scene/Sphere.hpp"
#include "scene/Triangle.hpp"
#include "scene/Cylinder.hpp"
#include "maths/Point.hpp"
#include "maths/Vector.hpp"
#include "maths/Ray.hpp"

#include <chrono>

namespace scene {
    Scene::Scene() : camera(Camera(maths::Point())) {

    }

    Scene::Scene(YAML::Node root) {
        this->name = root["name"].as<std::string>();
        this->camera = root["camera"].as<Camera>();
        if (root["light"]) {
            this->insertLight(root["light"].as<Light>());
        } else if (root["lights"]) {
            auto lights = root["lights"];
            for (auto it = lights.begin(); it != lights.end(); ++it) {
                this->insertLight(it->second.as<Light>());
            }
        }

        YAML::Node objects = root["objects"];
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            std::string name = it->first.as<std::string>();
            std::string type = it->second["type"].as<std::string>();
            this->insertObj(this->nodeToObj(type, it->second));
        }
    }

    Scene::~Scene() {
        for (auto &obj : this->objs) {
            delete obj;
        }
        this->objs.clear();
    }

    const Light &Scene::getLight(int i) const {
        return this->lights[i];
    }

    const std::vector<Light> &Scene::getAllLights() const {
        return this->lights;
    }

    void Scene::insertLight(Light l) {
        this->lights.push_back(l);
    }

    const Object &Scene::getObj(int i) {
        return (*this->objs[i]);
    }

    const std::vector<Object*> &Scene::getAllObj() {
        return this->objs;
    }

    void Scene::insertObj(Object* obj) {
        this->objs.push_back(obj);
    }

    bool Scene::isShadow(const maths::Point& impact, const Light& light) const {
        maths::Ray toLight = light.getRayToLight(impact);
        for (auto& obj : this->objs)
        {
            maths::Point temp;
            if (obj->intersect(toLight, temp))
            {
                if (maths::Vector(temp - impact).norm() < maths::Vector(light.getPos() - impact).norm())
                    return true;
            }
        }
        return false;
    }

    std::thread Scene::render(cv::Mat* mat, std::promise<std::string> &&p, std::atomic<bool> &done) const {
        auto handle = std::thread([mat, this, &p, &done]() {
            unsigned int numThreads = 8;
            std::thread threads[numThreads];
            auto startTime = std::chrono::high_resolution_clock::now();

            for (int threadIdx = 0; threadIdx < numThreads; ++threadIdx) {
                threads[threadIdx] = std::thread([ numThreads, mat, this ](int idx) {
                    for (int i = 0; i < mat->rows; ++i) {
                        if (i % numThreads != idx) {
                            continue;
                        }

                        for (int j = 0; j < mat->cols; ++j) {
                            auto &bgra = mat->at<cv::Vec4b>(i, j);
                            bgra[0] = static_cast<uchar>(0.0f);
                            bgra[1] = static_cast<uchar>(0.0f);
                            bgra[2] = static_cast<uchar>(0.0f);
                            bgra[3] = static_cast<uchar>(255.0f);

                            // x val [0, 1]
                            float x = (float)j / (float)mat->cols;
                            // y val [0, 1]
                            float y = (float)i / (float)mat->rows;

                            maths::Ray ray = this->camera.getRay(x, y);
                            maths::Point impact;
                            maths::Point closestImpact;
                            float minDist = -1.0f;
                            float impactDist;
                            scene::Object* closest = nullptr;
                            for (auto &obj : this->objs) {
                                if (obj->intersect(ray, impact)) {
                                    impactDist = maths::Vector(impact - this->camera.getPos()).norm();
                                    if (minDist < 0.0f || impactDist < minDist) {
                                        closest = obj;
                                        minDist = impactDist;
                                        closestImpact = impact;
                                    }
                                }
                            }
                            if (closest != nullptr) {
                                Color c = this->camera.getImpactColor(ray, *closest, closestImpact, *this);
                                bgra[0] = cv::saturate_cast<uchar>(c.b() * 255.0f);
                                bgra[1] = cv::saturate_cast<uchar>(c.g() * 255.0f);
                                bgra[2] = cv::saturate_cast<uchar>(c.r() * 255.0f);
                            }
                        }
                    }
                }, threadIdx);
            }

            for (auto &thread : threads) {
                thread.join();
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            std::stringstream ss;
            ss << "Execution time: ";
            if (duration >= 1000.0f) {
                float seconds = duration / 1000.0f;
                if (seconds >= 60.0f) {
                    float minutes = (int)(seconds / 60.0f);
                    seconds -= minutes * 60.0f;
                    ss << minutes << ":" << (int)seconds << ".";
                } else {
                    ss << seconds << " seconds.";
                }
            } else {
                ss << duration << " milliseconds.";
            }
            p.set_value(ss.str());

            done.store(true);
        });

        return handle;
    }

    Object* Scene::nodeToObj(const std::string &type, const YAML::Node &node) {
        Object *obj = nullptr;

        if (type == "plane") obj = new Plane();
        if (type == "square") obj = new Square();
        if (type == "cube") obj = new Cube();
        if (type == "sphere") obj = new Sphere();
        if (type == "triangle") obj = new Triangle();
        if (type == "cylinder") obj = new Cylinder();

        if (obj != nullptr) {
            obj->fromYaml(node);
        }
        return obj;
    }

    const Camera &Scene::getCamera() const {
        return camera;
    }

    void Scene::setCamera(const Camera &camera) {
        Scene::camera = camera;
    }

    const std::string &Scene::getName() const {
        return this->name;
    }
}