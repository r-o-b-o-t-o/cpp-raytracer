#include "scene/Square.hpp"

#include <cmath>

namespace Scene {
    Square::Square(const Math::Point &point) : Plane(point){

    }

    bool Square::intersect(const Math::Ray &ray, Math::Point &impact) const {
        Math::Ray rayon = this->globalToLocal(ray);
        auto t = -(rayon.getOrigin()[2]/rayon.getVector()[2]);
        
        if (t < 0)
            return false;
        impact = rayon.getOrigin() + t*rayon.getVector();
        if ((impact[0] < -1 || impact[0] > 1) || (impact[1] < -1 || impact[1] > 1))
            return false;
        impact = this->localToGlobal(impact);
        
        return true;
    }
}
