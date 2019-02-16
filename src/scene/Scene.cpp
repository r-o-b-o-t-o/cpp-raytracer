#include "scene/Scene.hpp"
#include "scene/Plane.hpp"
#include "scene/Square.hpp"
#include "scene/Cube.hpp"
#include "scene/Sphere.hpp"
#include "maths/Point.hpp"

namespace scene {
    Scene::Scene() : camera(Camera(maths::Point())) {

    }

    Scene::Scene(YAML::Node root) {
        this->camera = root["camera"].as<Camera>();
        this->insertLight(root["light"].as<Light>());

        YAML::Node objects = root["objects"];
        for (YAML::const_iterator it = objects.begin(); it != objects.end(); ++it) {
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

    bool Scene::isShadow(const maths::Point& impact, const Light& light){
        for (auto& obj : this->objs)
        {

        }
    }

    cv::Mat Scene::render(int height, int width) const {
        cv::Mat mat(height, width, CV_8UC4);

        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.cols; ++j) {
                auto &bgra = mat.at<cv::Vec4b>(i, j);
                bgra[0] = static_cast<uchar>(0.0f);
                bgra[1] = static_cast<uchar>(0.0f);
                bgra[2] = static_cast<uchar>(0.0f);
                bgra[3] = static_cast<uchar>(255.0f);

                // x val [0, 1]
                float x = (float)j / (float)mat.cols;
                // y val [0, 1]
                float y = (float)i / (float)mat.rows;

                maths::Ray ray = this->camera.getRay(x, y);
                maths::Point impact;
                float minDist = -1.0f;
                float impactDist;
                scene::Object *closest = nullptr;
                for (auto &obj : this->objs) {
                    if (obj->intersect(ray, impact)) {
                        impactDist = (maths::Vector(impact) - maths::Vector(this->camera.getPos())).norm();
                        if (minDist < 0.0f || impactDist < minDist) {
                            closest = obj;
                        }
                    }
                }
                if (closest != nullptr) {
                    Color c = this->camera.getImpactColor(ray, *closest, impact, *this);
                    bgra[0] = cv::saturate_cast<uchar>(c.b() * 255.0f);
                    bgra[1] = cv::saturate_cast<uchar>(c.g() * 255.0f);
                    bgra[2] = cv::saturate_cast<uchar>(c.r() * 255.0f);
                }
            }
        }

        return mat;
    }

    void Scene::exportImage(const std::string &name) {
        std::string imgName(name);
        imgName.append(".png");
        std::cout << "Exporting image to \"" << imgName << "\"..." << std::endl;

        int height = static_cast<int>(this->camera.getHeight());
        int width = static_cast<int>(this->camera.getWidth());

        auto mat = this->render(height, width);

        std::vector<int> compressionParams;
        compressionParams.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compressionParams.push_back(9);

        try {
            imwrite(imgName, mat, compressionParams);
#ifdef _WIN32
            imgName = "\"" + imgName + "\"";
            system(imgName.c_str());
#endif
        } catch (std::runtime_error &ex) {
            std::cerr << "Exception converting image to PNG format: " << ex.what() << std::endl;
            return;
        }
        std::cout << "Saved PNG file." << std::endl;
    }

    Object* Scene::nodeToObj(const std::string &type, const YAML::Node &node) {
        Object *obj = nullptr;

        if (type == "plane") obj = new Plane();
        if (type == "square") obj = new Square();
        if (type == "cube") obj = new Cube();
        if (type == "sphere") obj = new Sphere();

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
}