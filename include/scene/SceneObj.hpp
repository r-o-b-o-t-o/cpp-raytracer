#ifndef SCENE_HPP
#define SCENE_HPP

#include "scene/Camera.hpp"
#include "scene/Object.hpp"
#include "scene/Light.hpp"
#include <vector>

namespace Scene {
    class SceneObj {
        public:

        SceneObj();
        Scene::Light getLight(int);
        std::vector<Scene::Light> getAllLights();
        void insertLight(Light);

        Scene::Object* getObj(int);
        std::vector<Scene::Object*> getAllObj();
        void insertObj(Scene::Object*);

        Scene::Camera getCamera();
        void setCamera(Scene::Camera);
        private:
        Camera camera;
        std::vector<Scene::Object*> objs;
        std::vector<Scene::Light> lights;
    };
}

#endif // SCENE_HPP