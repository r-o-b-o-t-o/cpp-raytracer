#include "math/Point.hpp"
#include "math/Vector.hpp"

namespace maths {
    Point::Point() {
        for (float &value : this->values) {
            value = 0.0f;
        }
    }

    Point::Point(float x, float y, float z) {
        this->x(x);
        this->y(y);
        this->z(z);
    }

    Point::Point(const Point &p) {
        *this = p;
    }

    Point::Point(const Vector &v) {
        *this = v;
    }

    Point::operator Vector() const {
        return Vector(*this);
    }

    Point &Point::operator=(const Point &p) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] = p[i];
        }
        return *this;
    }

    Point &Point::operator=(const Vector &v) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] = v[i];
        }
        return *this;
    }

    float Point::dot(const Point &other) {
        float product = 0.0f;
        for (int i = 0; i < 3; ++i) {
            product += (*this)[i] * other[i];
        }
        return product;
    }

    float &Point::operator[](const int idx) {
        return this->values[idx];
    }

    const float &Point::operator[](const int idx) const {
        return this->values[idx];
    }

    std::ostream &operator<<(std::ostream &s, const Point &p) {
        s << "Point { " << p[0] << " ; " << p[1] << " ; " << p[2] << " }";
        return s;
    }

    Point Point::operator+(const Point &other) const {
        Point p(*this);
        p += other;
        return p;
    }

    Point &Point::operator+=(const Point &rhs) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] += rhs[i];
        }
        return *this;
    }

    Point Point::operator+(const Vector &other) const {
        return *this + Point(other);
    }

    Point &Point::operator+=(const Vector &rhs) {
        this->operator+=(Point(rhs));
        return *this;
    }

    Point Point::operator-(const Point &other) const {
        Point p(*this);
        p -= other;
        return p;
    }

    Point &Point::operator-=(const Point &rhs) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] -= rhs[i];
        }
        return *this;
    }

    Point Point::operator-(const Vector &other) const {
        return *this - Point(other);
    }

    Point &Point::operator-=(const Vector &rhs) {
        this->operator-=(Point(rhs));
        return *this;
    }

    Point Point::operator-() const {
        Point p(0.0f, 0.0f, 0.0f);
        return p - *this;
    }

    Point Point::operator*(const float &mul) const {
        Point p(*this);
        p *= mul;
        return p;
    }

    Point &Point::operator*=(const float &mul) {
        for (float &value : this->values) {
            value *= mul;
        }
        return *this;
    }

    Point Point::operator/(const float &mul) const {
        Point p(*this);
        p /= mul;
        return p;
    }

    Point &Point::operator/=(const float &mul) {
        *this *= (1.0f / mul);
        return *this;
    }

    Point operator*(const float &mul, const Point &p) {
        return Point(p * mul);
    }

    float Point::x() const {
        return (*this)[0];
    }

    float Point::y() const {
        return (*this)[1];
    }

    float Point::z() const {
        return (*this)[2];
    }

    void Point::x(float val) {
        (*this)[0] = val;
    }

    void Point::y(float val) {
        (*this)[1] = val;
    }

    void Point::z(float val) {
        (*this)[2] = val;
    }
}
