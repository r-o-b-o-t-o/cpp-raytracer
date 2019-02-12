#include "math/Ray.hpp"

namespace Math {
    Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz)
        : origin(ox, oy, oz),
          vector(vx, vy, vz) {
    }

    Ray::Ray(Point o, Vector v)
        : origin(o),
          vector(v) {
    }

    const Point &Math::Ray::getOrigin() const {
        return this->origin;
    }

    const Vector &Math::Ray::getVector() const {
        return this->vector;
    }
}
