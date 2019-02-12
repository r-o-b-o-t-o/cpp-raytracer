#include <math.h>
#include "Vector.hpp"

namespace Math {
    Vector::Vector() : Point() { }

    Vector::Vector(float x, float y, float z) : Point(x, y, z) { }

    Vector::Vector(const Point &p) : Point(p) { }

    float Vector::norm() const {
        float sum = 0.0f;
        for (float value : this->values) {
            sum += powf(value, 2.0f);
        }
        return sqrt(sum);
    }

    void Vector::normalize() {
        float norm = this->norm();
        for (float &value : this->values) {
            value /= norm;
        }
    }

    Vector Vector::normalized() const {
        Vector v(*this);
        v.normalize();
        return v;
    }

    std::ostream &operator<<(std::ostream &s, const Vector &v) {
        s << "Vector { " << v[0] << " ; " << v[1] << " ; " << v[2] << " }";
        return s;
    }

    Point::Point(const Vector &v) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] = v[i];
        }
    }
}
