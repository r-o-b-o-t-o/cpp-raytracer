#include "scene/Square.hpp"

#include <cmath>

namespace Scene {
    bool Square::intersect(const Math::Ray &ray, Math::Point &impact) const {
        auto r = this->globalToLocal(ray);
        auto t = -r.getOrigin().z() / r.getVector().z();
        if (fabs(t) < 0.00001f) {
            return false;
        }

        impact = ray.getOrigin() + t * ray.getVector();
        return true;
    }
}
