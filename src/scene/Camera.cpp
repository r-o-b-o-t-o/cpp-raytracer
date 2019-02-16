#include "scene/Camera.hpp"
#include "scene/Scene.hpp"

namespace scene {
    Camera::Camera() : Entity() {

    }

    Camera::Camera(maths::Point point) : Entity(point) {
        this->focal = 2.0f;
    }

    //methode de la classe Camera
    //retourne le Ray (dans le référenciel local, pour le moment)
    //correspondant au point (x,y) de la camera, 
    //chaque coordonnée étant dans l'intervalle [0;1]
    maths::Ray Camera::getRay(float x, float y) const {
        // calculer le point de l ecran P en Ref Local
        maths::Point p(2 * x - 1, 2 * y - 1, 0);
        maths::Point f(0.0f, 0.0f, getFocal());
        // calculer le vecteur passant par le point focal et P
        maths::Vector v(p - f);
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
            auto dot = L.dot(N);
            if (dot > 0.0f) {
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
}