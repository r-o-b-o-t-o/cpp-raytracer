#include "scene/Plane.hpp"

#include <cmath>

namespace Scene {
    bool Plane::intersect(const Math::Ray &ray, Math::Point &impact) const {
        auto r = this->globalToLocal(ray);
        auto t = -r.getOrigin().z() / r.getVector().z();
        if (fabs(t) < 0.00001f) {
            return false;
        }

        impact = ray.getOrigin() + t * ray.getVector();
        return true;
    }

    Math::Ray Plane::getNormal(const Math::Point &impact, const Math::Point &observator) const {
        Math::Ray nal(this->globalToLocal(impact), Math::Vector(0, 0, this->globalToLocal(observator).z()));
        return this->localToGlobal(nal.normalized());
    }
}
