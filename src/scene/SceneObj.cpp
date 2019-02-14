#include "scene/SceneObj.hpp"

namespace Scene {
    
    SceneObj::SceneObj(): camera(Scene::Camera(Math::Point())){
    }

    Scene::Light SceneObj::getLight(int i){
        return this->lights[i];
    }

    std::vector<Scene::Light> SceneObj::getAllLights(){
        return this->lights;
    }
    
    void SceneObj::insertLight(Scene::Light l){
        this->lights.push_back(l);
    }

    Scene::Object* SceneObj::getObj(int i){
        return this->objs[i];
    }

    std::vector<Object*> SceneObj::getAllObj(){
        return this->objs;
    }

    void SceneObj::insertObj(Object* obj){
        this->objs.push_back(obj);
    }

    Scene::Camera SceneObj::getCamera(){
        return this->camera;
    }

    void SceneObj::setCamera(Scene::Camera cam){
        this->camera = cam;
    }
}