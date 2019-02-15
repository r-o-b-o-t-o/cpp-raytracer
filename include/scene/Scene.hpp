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

        scene::Light getLight(int);
        std::vector<scene::Light> getAllLights();
        void insertLight(Light);

        scene::Object* getObj(int);
        std::vector<scene::Object*> &getAllObj();
        void insertObj(scene::Object*);

        const Camera &getCamera() const;
        void setCamera(const Camera &camera);

        void exportImage(int height, int width);

    protected:
        Camera camera;
        std::vector<scene::Object*> objs;
        std::vector<scene::Light> lights;

        cv::Mat createColorsMat(int height, int width);
        scene::Object* nodeToObj(const std::string &type, const YAML::Node &obj);
    };
}

#endif // SCENE_HPP