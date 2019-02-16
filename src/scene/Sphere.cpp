#include "scene/Sphere.hpp"

#include <cmath>

namespace scene {
    Sphere::Sphere(const maths::Point &point) : Object(point) {

    }

    bool Sphere::intersect(const maths::Ray &ray, maths::Point &impact) const {
        maths::Ray r = this->globalToLocal(ray);
        float a = powf(r.getVector()[0], 2) + powf(r.getVector()[1], 2) + powf(r.getVector()[2], 2);
        float b = 2 * (r.getOrigin()[0] * r.getVector()[0] + r.getOrigin()[1] * r.getVector()[1] + r.getOrigin()[2] * r.getVector()[2]);
        float c = powf(r.getOrigin()[0], 2) + powf(r.getOrigin()[1], 2) + powf(r.getOrigin()[2], 2) - 1;

        float det = powf(b, 2) - (4 * a * c);
        float rac = 0;
        if (det < 0)
            return false;
        if (det == 0)
            rac = -(b / (2 * a));
        if (det > 0) {
            float rac1 = -((b - sqrtf(det)) / (2 * a));
            float rac2 = -((b + sqrtf(det)) / (2 * a));
            if (rac1 < rac2)
                rac = rac1;
            else
                rac = rac2;

            if (rac1 < 0)
                rac = rac2;
            if (rac2 < 0)
                rac = rac1;

        }
        impact = r.getOrigin() + rac * r.getVector();
        impact = this->localToGlobal(impact)+ this->getNormal(impact, r.getOrigin()).getVector();
        
        return true;
    }

    maths::Ray Sphere::getNormal(const maths::Point &impact, const maths::Point &observator) const {
        auto localImpact = globalToLocal(impact);
        maths::Vector localObs(globalToLocal(observator));
        maths::Ray nal(localImpact, maths::Vector(localImpact));
        if (localObs.norm() <= 1.0) {
            nal.setVector(-nal.getVector());
        }
        return localToGlobal(nal).normalized();
    }
}
