#include "maths/HPoint.hpp"

namespace maths {
    HPoint::HPoint()
            : _w(1.0f),
              Point() {

    }

    HPoint::HPoint(float x, float y, float z)
            : _w(1.0f),
              Point(x, y, z) {

    }

    HPoint::HPoint(float x, float y, float z, float w)
            : _w(w),
              Point(x, y, z) {

    }

    HPoint::HPoint(const HPoint &p)
            : _w(1.0f),
              Point(p) {

    }

    HPoint::HPoint(const HPoint &p, float w)
            : _w(w),
              Point(p) {

    }

    HPoint::HPoint(const Point &p)
            : _w(1.0f),
              Point(p) {

    }

    HPoint::HPoint(const Point &p, float w)
            : _w(w),
              Point(p) {

    }

    float HPoint::x() const {
        return Point::x() / this->_w;
    }

    float HPoint::y() const {
        return Point::y() / this->_w;
    }

    float HPoint::z() const {
        return Point::z() / this->_w;
    }

    float HPoint::w() const {
        return this->_w;
    }
}
