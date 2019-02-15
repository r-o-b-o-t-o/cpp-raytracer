#include "maths/Vector.hpp"

#include <math.h>

namespace maths {
    Vector::Vector() {
        for (float &value : this->values) {
            value = 0.0f;
        }
    }

    Vector::Vector(float x, float y, float z) {
        this->x(x);
        this->y(y);
        this->z(z);
    }

    Vector::Vector(const Vector &v) {
        *this = v;
    }

    Vector::Vector(const Point &p) {
        *this = p;
    }

    Vector::operator Point() const {
        return Point(*this);
    }

    Vector &Vector::operator=(const Vector &v) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] = v[i];
        }
        return *this;
    }

    Vector &Vector::operator=(const Point &p) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] = p[i];
        }
        return *this;
    }

    float Vector::dot(const Vector &other) const {
        float product = 0.0f;
        for (int i = 0; i < 3; ++i) {
            product += (*this)[i] * other[i];
        }
        return product;
    }

    float Vector::dot(const Point &other) const {
        return this->dot(Vector(other));
    }

    float &Vector::operator[](const int idx) {
        return this->values[idx];
    }

    const float &Vector::operator[](const int idx) const {
        return this->values[idx];
    }

    std::ostream &operator<<(std::ostream &s, const Vector &v) {
        s << "Vector { " << v[0] << " ; " << v[1] << " ; " << v[2] << " }";
        return s;
    }

    float Vector::norm() const {
        float sum = 0.0f;
        for (float value : this->values) {
            sum += powf(value, 2.0f);
        }
        return sqrt(sum);
    }

    void Vector::normalize() {
        this->operator/(this->norm());
    }

    Vector Vector::normalized() const {
        Vector v(*this);
        v.normalize();
        return v;
    }

    Vector Vector::operator+(const Vector &other) const {
        Vector v(*this);
        v += other;
        return v;
    }

    Vector &Vector::operator+=(const Vector &rhs) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] += rhs[i];
        }
        return *this;
    }

    Vector Vector::operator+(const Point &other) const {
        return *this + Vector(other);
    }

    Vector &Vector::operator+=(const Point &rhs) {
        this->operator+=(Vector(rhs));
        return *this;
    }

    Vector Vector::operator-(const Vector &other) const {
        Vector v(*this);
        v -= other;
        return v;
    }

    Vector &Vector::operator-=(const Vector &rhs) {
        for (int i = 0; i < 3; ++i) {
            (*this)[i] -= rhs[i];
        }
        return *this;
    }

    Vector Vector::operator-(const Point &other) const {
        return *this - Vector(other);
    }

    Vector &Vector::operator-=(const Point &rhs) {
        this->operator-=(Vector(rhs));
        return *this;
    }

    Vector Vector::operator-() const {
        Vector v(0.0f, 0.0f, 0.0f);
        return v - *this;
    }

    Vector Vector::operator*(const float &mul) const {
        Vector v(*this);
        v *= mul;
        return v;
    }

    Vector &Vector::operator*=(const float &mul) {
        for (float &value : this->values) {
            value *= mul;
        }
        return *this;
    }

    Vector Vector::operator/(const float &mul) const {
        Vector v(*this);
        v /= mul;
        return v;
    }

    Vector &Vector::operator/=(const float &mul) {
        *this *= (1.0f / mul);
        return *this;
    }

    Vector operator*(const float &mul, const Vector &v) {
        return Vector(v * mul);
    }

    float Vector::x() const {
        return (*this)[0];
    }

    float Vector::y() const {
        return (*this)[1];
    }

    float Vector::z() const {
        return (*this)[2];
    }

    void Vector::x(float val) {
        (*this)[0] = val;
    }

    void Vector::y(float val) {
        (*this)[1] = val;
    }

    void Vector::z(float val) {
        (*this)[2] = val;
    }
}
