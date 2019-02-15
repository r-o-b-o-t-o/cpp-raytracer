#include "scene/Camera.hpp"
#include "scene/Scene.hpp"

namespace scene {
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
        maths::Ray nal = obj.getNormal(impact, ray.getOrigin());
        scene::Material t = obj.getMaterial(impact);
        scene::Color col = t.getKa();
        auto lights = scene.getAllLights().size();

        for (int i = 0; i < lights; i++) {
            auto &lum = scene.getLight(i);
            float coef = lum.getVectorToLight(impact).dot(nal.getVector());
            auto spec = (2 * coef * nal.getVector()) - lum.getVectorToLight(impact);

            if (coef > 0) {
                col += coef * t.getKd().mul(lum.getDiffuseColor());
                col += lum.getSpecularColor().mul(t.getKs() * powf(spec.dot(-ray.getVector()), t.getShininess()));
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