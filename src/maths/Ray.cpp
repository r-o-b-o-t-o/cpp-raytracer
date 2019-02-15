#include "maths/Ray.hpp"

namespace maths {
    Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz)
            : origin(ox, oy, oz),
              vector(vx, vy, vz) {
    }

    Ray::Ray(Point o, Vector v)
            : origin(o),
              vector(v) {
    }

    const Point &Ray::getOrigin() const {
        return this->origin;
    }

    void Ray::setOrigin(const Point &p) {
        this->origin = p;
    }

    const Vector &Ray::getVector() const {
        return this->vector;
    }

    void Ray::setVector(const Vector &v) {
        this->vector = v;
    }

    void Ray::normalize() {
        this->vector.normalize();
    }

    Ray Ray::normalized() const {
        Ray r(*this);
        r.normalize();
        return r;
    }
}
