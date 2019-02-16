#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include <iostream>

namespace scene {
    Camera::Camera() : Entity() {
        this->shadow = false;
    }

    Camera::Camera(maths::Point point) : Entity(point) {
        this->focal = 2.0f;
        this->shadow = false;
    }

    //methode de la classe Camera
    //retourne le Ray (dans le référenciel local, pour le moment)
    //correspondant au point (x,y) de la camera, 
    //chaque coordonnée étant dans l'intervalle [0;1]
    maths::Ray Camera::getRay(float x, float y) const {
        // calculer le point de l ecran P en Ref Local

        maths::Point p(2*x -1, 2*y-1, 0);
        maths::Point f(0.0f, 0.0f, getFocal());
        maths::Vector v(p - f);

        //x = (x+0.5f) / this->getSize() - this->getWidth() / this->getSize() / 2.0f;
        //y = (y+0.5f) / this->getSize() - this->getHeight() / this->getSize() /2.0f;
        //maths::Point p(-x, -y, 0);
        //maths::Vector v(-x, -y, this->getFocal());
        // creer le rayon R d origine P et de direction V
        maths::Ray r(p, v);
        // passer R dans le ref global => R'
        maths::Ray r2 = this->localToGlobal(r);
        // normaliser R'
        // return R'

        return r2.normalized();
    }

    //Retourne la couleur au point d'impact entre l'objet et le rayon, en fonction des éléments de la scène.
    //Le modèle d'illumination est ici celui de Phong.
    scene::Color Camera::getImpactColor(const maths::Ray &ray, const scene::Object &obj, const maths::Point &impact, const scene::Scene &scene) const {
        auto m = obj.getMaterial(impact);
        Color ambiant(1.0f, 1.0f, 1.0f); // TODO
        Color col = m.getKa().mul(ambiant);
        auto N = obj.getNormal(impact, ray.getOrigin()).getVector();

        for (auto &light : scene.getAllLights()) {
            auto L = light.getVectorToLight(impact);
            //std::cout << "VectorToLight :" << L[0] << ","<<L[1]<< "," <<L[2] << std::endl
            if (this->shadow && scene.isShadow(impact, light))
                continue;
            auto dot = L.dot(N);
            if (dot > 0.0f) {
                //std::cout << "dot > 0.0" << std::endl;
                col += dot * m.getKd().mul(light.getDiffuseColor());

                auto R = 2.0f * dot * N - L;
                auto V = -ray.getVector();
                col += m.getKs().mul(light.getSpecularColor()) * dot * powf(R.dot(V), m.getShininess());
            }
        }

        return col;
    }

    void Camera::setFocal(float focal) {
        this->focal = focal;
    }

    float Camera::getFocal() const {
        return this->focal;
    }


    void Camera::setWidth(float width) {
        this->width = width;
    }
    float Camera::getWidth() const{
        return this->width;
    }
    void Camera::setHeight(float height){
        this->height = height;
    }
    float Camera::getHeight() const{
        return this->height;
    }
    void Camera::setSize(float size){
        this->size = size;
    }
    float Camera::getSize() const{
        return this->size;
    }
    void Camera::setShadow(bool s){
        this->shadow = s;
    }
    bool Camera::getShadow() const{
        return this->shadow;
    }
}