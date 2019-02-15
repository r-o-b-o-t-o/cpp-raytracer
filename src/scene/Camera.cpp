#include "scene/Camera.hpp"
#include <iostream>

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


    void Camera::setFocal(float focal) {
        this->focal = focal;
    }

    float Camera::getFocal() const {
        return this->focal;
    }
}