#include "scene/Plane.hpp"

namespace scene {
    Plane::Plane(const maths::Point &point) : Object(point) {

    }

    bool Plane::intersect(const maths::Ray &ray, maths::Point &impact) const {
        auto r = this->globalToLocal(ray);
        auto t = -r.getOrigin().z() / r.getVector().z();
        if (t < 0.0f) {
            return false;
        }

        impact = r.getOrigin() + t * r.getVector();
        impact = this->localToGlobal(impact) + this->getNormal(impact, ray.getOrigin()).getVector() * 0.0005f;
        return true;
    }

    maths::Ray Plane::getNormal(const maths::Point &impact, const maths::Point &observator) const {
        maths::Ray nal(this->globalToLocal(impact), maths::Vector(0, 0, this->globalToLocal(observator).z()));
        return this->localToGlobal(nal.normalized());
    }

    maths::Point Plane::getTextureCoordinates(const maths::Point &point) const {
        auto p = globalToLocal(point);

        maths::Point textCoords;
        for (int i = 0; i < 2; ++i) {
            if (p[i] < 0.0f) {
                textCoords[i] = 1 - (int(p[i]) - p[i]);
            } else {
                textCoords[i] = p[i] - int(p[i]);
            }
        }

        return textCoords;
    }

    maths::Point Plane::getMaterialCoordinates(const maths::Point &point) const {
        return this->getTextureCoordinates(point);
    }
}
