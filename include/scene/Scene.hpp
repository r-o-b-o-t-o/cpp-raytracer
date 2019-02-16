#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>

#include "scene/Camera.hpp"
#include "scene/Object.hpp"
#include "scene/Light.hpp"

namespace scene {
    class Scene {
    public:
        Scene();
        explicit Scene(YAML::Node root);
        ~Scene();

        const Light &getLight(int) const;
        const std::vector<Light> &getAllLights() const;
        void insertLight(Light);

        const Object &getObj(int);
        const std::vector<Object*> &getAllObj();
        void insertObj(Object*);

        const Camera &getCamera() const;
        bool isShadow(const maths::Point& impact, const Light& light) const;
        void setCamera(const Camera &camera);
        
        void exportImage(const std::string &name);
    protected:
        Camera camera;
        std::vector<Object*> objs;
        std::vector<Light> lights;

        cv::Mat render(int height, int width) const;
        Object* nodeToObj(const std::string &type, const YAML::Node &obj);
    };
}

#endif // SCENE_HPP