#include "scene/Cube.hpp"

#include <cmath>

namespace scene {
    Cube::Cube(const maths::Point &point) : Object(point) {

    }

    bool Cube::intersect(const maths::Ray &ray, maths::Point &impact) const {
        maths::Ray nal = this->globalToLocal(ray).normalized();

        float tMin = -1.0f;
        float offsets[] = { -1.0f, 1.0f };
        for (int d = 0; d < 3; d++) {
            for (float offset : offsets) {
                float t = this->intersectsSide(nal, d, offset);
                if (t >= 0.0f && (tMin < 0.0f || tMin > t)) {
                    tMin = t;
                }
            }
        }

        if (tMin >= 0.0f) {
            impact = this->localToGlobal(nal.getOrigin() + tMin * nal.getVector());
            return true;
        }

        return false;
    }

    float Cube::intersectsSide(const maths::Ray &r, int dim, float offset) const {
        float epsilon = 0.00001f;

        if (r.getVector()[dim] < epsilon && r.getVector()[dim] > -epsilon) {
            return -1.0f;
        }
        float t = (offset - r.getOrigin()[dim]) / r.getVector()[dim];
        if (t < 0.0f) {
            return -1.0f;
        }
        for (int d = 0; d < 3; d++) {
            if (d == dim) {
                continue;
            }
            float x = r.getOrigin()[d] + t * r.getVector()[d];
            if (x < -1 || x > 1) {
                return -1.0f;
            }
        }
        return t;
    }

    maths::Ray Cube::getNormal(const maths::Point &impact, const maths::Point &observer) const {
        auto localImpact = globalToLocal(impact);
        auto localObs = globalToLocal(observer);
        float epsilon = 0.00001f;
        maths::Vector v(0.0f, 0.0f, 0.0f);

        if (std::fabs(localImpact.x() - -1.0f) < epsilon) {
            v.x(-1.0f);
        }
        if (std::fabs(localImpact.x() - 1.0f) < epsilon) {
            v.x(1.0f);
        }
        if (std::fabs(localImpact.y() - -1.0f) < epsilon) {
            v.y(-1.0f);
        }
        if (std::fabs(localImpact.y() - 1.0f) < epsilon) {
            v.y(1.0f);
        }
        if (std::fabs(localImpact.z() - -1.0f) < epsilon) {
            v.z(-1.0f);
        }
        if (std::fabs(localImpact.z() - 1.0f) < epsilon) {
            v.z(1.0f);
        }

        maths::Ray nal(localImpact, v);
        if (localObs.x() > -1.0f && localObs.x() < 1.0f &&
            localObs.y() > -1.0f && localObs.y() < 1.0f &&
            localObs.z() > -1.0f && localObs.z() < 1.0f) {
            nal.setVector(-nal.getVector());
        }
        return localToGlobal(nal).normalized();
    }

    maths::Point Cube::getTextureCoordinates(const maths::Point &point) const {
        auto p = globalToLocal(point);
        float epsilon = 0.00001f;

        if ((std::fabs(p.x() - -1.0f) < epsilon) || (std::fabs(p.x() - 1.0f) < epsilon)) { // x == -1 || x == 1
            p.x(p.z() / 2.0f + 0.5f);
            p.y(p.y() / 2.0f + 0.5f);
        }
        if ((std::fabs(p.y() - -1.0f) < epsilon) || (std::fabs(p.y() - 1.0f) < epsilon)) { // y == -1 || y == 1
            p.x(p.x() / 2.0f + 0.5f);
            p.y(p.z() / 2.0f + 0.5f);
        }
        if ((std::fabs(p.z() - -1.0f) < epsilon) || (std::fabs(p.z() - 1.0f) < epsilon)) { // z == -1 || z == 1
            p.x(p.x() / 2.0f + 0.5f);
            p.y(p.y() / 2.0f + 0.5f);
        }
        return p;
    }

    maths::Point Cube::getMaterialCoordinates(const maths::Point &p) const {
        return this->getTextureCoordinates(p);
    }
}
