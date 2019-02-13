#include "math/HVector.hpp"

namespace Math {
    HVector::HVector()
            : _w(1.0f),
              Vector() {

    }

    HVector::HVector(float x, float y, float z)
            : _w(1.0f),
              Vector(x, y, z) {

    }

    HVector::HVector(float x, float y, float z, float w)
            : _w(w),
              Vector(x, y, z) {

    }

    HVector::HVector(const HVector &v)
            : _w(1.0f),
              Vector(v) {

    }

    HVector::HVector(const HVector &v, float w)
            : _w(w),
              Vector(v) {

    }

    HVector::HVector(const Vector &v)
            : _w(1.0f),
              Vector(v) {

    }

    HVector::HVector(const Vector &v, float w)
            : _w(w),
              Vector(v) {

    }

    float HVector::x() const {
        return Vector::x() / this->_w;
    }

    float HVector::y() const {
        return Vector::y() / this->_w;
    }

    float HVector::z() const {
        return Vector::z() / this->_w;
    }

    float HVector::w() const {
        return this->_w;
    }
}
