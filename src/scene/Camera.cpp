#include "scene/Camera.hpp"
#include "math/Point.hpp"
#include "math/Vector.hpp"

namespace Scene {

    Camera::Camera(Math::Point point): Entity(point) {
        this->focal = 2.0f;
    }

    //methode de la classe Camera
    //retourne le Ray (dans le référenciel local, pour le moment)
    //correspondant au point (x,y) de la camera, 
    //chaque coordonnée étant dans l'intervalle [0;1]
    Math::Ray Camera::getRay(float x, float y)const {
        // calculer le point de l ecran P en Ref Local
        Math::Point p(2*x - 1, 2*y - 1, 0);
        Math::Point f(0, 0, this->focal);
        // calculer le vecteur passant par le point focal et P
        Math::Vector v = p - f;
        
        // creer le rayon R d origine P et de direction V
        Math::Ray r(p, v);
        // passer R dans le ref global => R'
        Math::Ray r2 = this->localToGlobal(r);
        // normaliser R'
        // return R'
        
        //return r2.normalized();
        return r2;
    }


    void Camera::getFocal(float focal){
        this->focal = focal;
    }

    float Camera::setFocal(){
        return this->focal;
    }

}