#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>

#include "scene/Camera.hpp"
#include "scene/Object.hpp"
#include "scene/Light.hpp"

namespace Scene {
    class SceneObj {
    public:
        SceneObj();
        explicit SceneObj(YAML::Node root);
        ~SceneObj();

        Scene::Light getLight(int);
        std::vector<Scene::Light> getAllLights();
        void insertLight(Light);

        Scene::Object* getObj(int);
        std::vector<Scene::Object*> &getAllObj();
        void insertObj(Scene::Object*);

        const Camera &getCamera() const;
        void setCamera(const Camera &camera);

        void exportImage(int height, int width);

    protected:
        Camera camera;
        std::vector<Scene::Object*> objs;
        std::vector<Scene::Light> lights;

        cv::Mat createColorsMat(int height, int width);
        Scene::Object* nodeToObj(const std::string &type, const YAML::Node &obj);
    };
}

#endif // SCENE_HPP