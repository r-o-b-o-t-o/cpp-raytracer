#include "scene/Square.hpp"

namespace scene {
    Square::Square(const maths::Point &point) : Plane(point) {

    }

    bool Square::intersect(const maths::Ray &ray, maths::Point &impact) const {
        maths::Ray rayon = this->globalToLocal(ray);
        auto t = -(rayon.getOrigin().z() / rayon.getVector().z());

        if (t < 0) {
            return false;
        }
        impact = rayon.getOrigin() + t * rayon.getVector();
        if ((impact.x() < -1.0f || impact.x() > 1.0f) || (impact.y() < -1.0f || impact.y() > 1.0f)) {
            return false;
        }
        impact = this->localToGlobal(impact) + this->getNormal(impact, ray.getOrigin()).getVector() * 0.0005f;

        return true;
    }

    maths::Point Square::getTextureCoordinates(const maths::Point &point) const {
        auto p = globalToLocal(point);
        maths::Point textCoords(p.x() / 2.0f + 0.5f, p.y() / 2.0f + 0.5f, 0.0f);
        return textCoords;
    }

    maths::Point Square::getMaterialCoordinates(const maths::Point &point) const {
        return Plane::getTextureCoordinates(point);
    }
}
