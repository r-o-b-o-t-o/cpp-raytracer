#include "scene/Cylindre.hpp"

#include <cmath>

namespace scene {
    Cylindre::Cylindre(const maths::Point &point) : Object(point) {

    }

    bool Cylindre::intersect(const maths::Ray &ray, maths::Point &impact) const {
        auto r = this->globalToLocal(ray);
        auto a = powf(r.getVector()[0], 2.0f) + powf(r.getVector()[2], 2.0f);
        auto b = 2.0f * (r.getOrigin()[0] * r.getVector()[0] + r.getOrigin()[2] * r.getVector()[2]);
        auto c = powf(r.getOrigin()[0], 2.0f) + powf(r.getOrigin()[2], 2.0f) - 1.0f;

        float t;
        auto d = powf(b, 2.0f) - 4.0f * a * c;
        if (d < 0.0f) {
            return false;
        } else if (fabs(d) < 0.0001) {
            t = -b / (2.0f * a);
        } else {
            auto x1 = (-b - sqrtf(d)) / (2.0f * a);
            auto x2 = (-b + sqrtf(d)) / (2.0f * a);
            if (x1 < 0.0f && x2 < 0.0f) {
                return false;
            }
            t = x1 < x2 ? x1 : x2;
            if (x1 < 0.0f) {
                t = x2;
            }
            if (x2 < 0.0f) {
                t = x1;
            }
        }

        impact = this->localToGlobal(r.getOrigin() + t * r.getVector());
        impact = impact + this->getNormal(impact, ray.getOrigin()).getVector();

        return true;
    }

    maths::Ray Cylindre::getNormal(const maths::Point &impact, const maths::Point &observator) const {
        auto localImpact = globalToLocal(impact);
        maths::Vector localObs(globalToLocal(observator));
        localObs[1] = 0.0f;

        maths::Ray nal(localImpact, maths::Vector(localImpact));
        if (localObs.norm() < 1.0) {
            nal.setVector(-nal.getVector());
        }
        nal.setVector(maths::Vector(nal.getVector()[0], 0, nal.getVector()[2]));
        return localToGlobal(nal).normalized();
    }

    maths::Point Cylindre::getTextureCoordinates(const maths::Point &point) const {
        auto p = globalToLocal(point);
        auto phi = acosf(p.z());
        auto theta = atan2f(p.y(), p.x());

        p.x((-theta + (float)M_PI) / (2.0f * (float)M_PI));
        p.y(phi / (float)M_PI);

        return p;
    }

    maths::Point Cylindre::getMaterialCoordinates(const maths::Point &point) const {
        auto p = globalToLocal(point);
        auto n = maths::Vector(p).normalized();
        p.x(0.5f + (atan2f(n.x(), n.z()) / (2 * (float)M_PI)));
        p.y((n.y() * 0.5f) + 0.5f);

        return p;
    }
}
