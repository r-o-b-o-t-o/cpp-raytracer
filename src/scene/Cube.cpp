#include "scene/Cube.hpp"

#include <cmath>

namespace scene {
    Cube::Cube(const maths::Point &point) : Object(point) {

    }

    bool Cube::intersect(const maths::Ray &ray, maths::Point &impact) const {
        return false;
    }

    maths::Ray Cube::getNormal(const maths::Point &impact, const maths::Point &observer) const {
        auto localImpact = globalToLocal(impact);
        auto localObs = globalToLocal(observer);
        float espilon = 0.00001f;
        maths::Vector v(0.0f, 0.0f, 0.0f);

        if (std::fabs(localImpact[0] - -1.0f) < espilon) {
            v[0] = -1.0f;
        }
        if (std::fabs(localImpact[0] - 1.0f) < espilon) {
            v[0] = 1.0f;
        }
        if (std::fabs(localImpact[1] - -1.0f) < espilon) {
            v[1] = -1.0f;
        }
        if (std::fabs(localImpact[1] - 1.0f) < espilon) {
            v[1] = 1.0f;
        }
        if (std::fabs(localImpact[2] - -1.0f) < espilon) {
            v[2] = -1.0f;
        }
        if (std::fabs(localImpact[2] - 1.0f) < espilon) {
            v[2] = 1.0f;
        }

        maths::Ray nal(localImpact, v);
        if (localObs[0] > -1.0f && localObs[0] < 1.0f &&
            localObs[1] > -1.0f && localObs[1] < 1.0f &&
            localObs[2] > -1.0f && localObs[2] < 1.0f) {
            nal.setVector(-nal.getVector());
        }
        return localToGlobal(nal).normalized();
    }
}
