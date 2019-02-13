#include "scene/Sphere.hpp"

#include <cmath>

namespace Scene {
    bool Sphere::intersect(const Math::Ray &ray, Math::Point &impact) const {
        auto r = this->globalToLocal(ray);
        auto t = -r.getOrigin().z() / r.getVector().z();
        if (fabs(t) < 0.00001f) {
            return false;
        }

        impact = ray.getOrigin() + t * ray.getVector();
        return true;
    }

    Math::Ray Sphere::getNormal(const Math::Point &impact, const Math::Point &observator) const {
        auto localImpact = globalToLocal(impact);
        Math::Vector localObs(globalToLocal(observator));
        Math::Ray nal(localImpact, Math::Vector(localImpact));
        if (localObs.norm() <= 1.0) {
            nal.setVector(-nal.getVector());
        }
        return localToGlobal(nal).normalized();
    }
}
