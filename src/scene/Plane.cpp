#include "scene/Plane.hpp"

#include <cmath>

namespace scene {

    Plane::Plane(const maths::Point &point): Object(point){

    }
    
    bool Plane::intersect(const maths::Ray &ray, maths::Point &impact) const {
        auto r = this->globalToLocal(ray);
        auto t = -r.getOrigin().z() / r.getVector().z();
        if (fabs(t) < 0.00001f) {
            return false;
        }

        impact = ray.getOrigin() + t * ray.getVector();
        return true;
    }

    maths::Ray Plane::getNormal(const maths::Point &impact, const maths::Point &observator) const {
        maths::Ray nal(this->globalToLocal(impact), maths::Vector(0, 0, this->globalToLocal(observator).z()));
        return this->localToGlobal(nal.normalized());
    }
}
