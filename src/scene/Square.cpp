#include "scene/Square.hpp"

#include <cmath>

namespace scene {
    Square::Square(const maths::Point &point) : Plane(point){

    }

    bool Square::intersect(const maths::Ray &ray, maths::Point &impact) const {
        maths::Ray rayon = this->globalToLocal(ray);
        auto t = -(rayon.getOrigin()[2]/rayon.getVector()[2]);
        
        if (t < 0)
            return false;
        impact = rayon.getOrigin() + t*rayon.getVector();
        if ((impact[0] < -1 || impact[0] > 1) || (impact[1] < -1 || impact[1] > 1))
            return false;
        impact = this->localToGlobal(impact)+ this->getNormal(impact, ray.getOrigin()).getVector() * 0.0005f; 
        
        return true;
    }
}
