#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"

namespace maths {
    class Vector {
    public:
        Vector();
        Vector(float x, float y, float z);
        Vector(const Vector &v);
        explicit Vector(const Point &p);
        explicit operator Point() const;
        Vector &operator=(const Vector &v);
        Vector &operator=(const Point &p);

        float dot(const Vector &other) const;
        float dot(const Point &other) const;

        float &operator[](int);
        const float &operator[](int) const;

        friend std::ostream &operator<<(std::ostream &s, const Vector &v);

        float norm() const;
        void normalize();
        Vector normalized() const;

        Vector operator+(const Vector &other) const;
        Vector &operator+=(const Vector &rhs);
        Vector operator+(const Point &other) const;
        Vector &operator+=(const Point &rhs);
        Vector operator-(const Vector &other) const;
        Vector &operator-=(const Vector &rhs);
        Vector operator-(const Point &other) const;
        Vector &operator-=(const Point &rhs);
        Vector operator-() const;
        Vector operator*(const float &mul) const;
        Vector &operator*=(const float &mul);
        Vector operator/(const float &mul) const;
        Vector &operator/=(const float &mul);
        friend Vector operator*(const float &mul, const Vector &p);

        virtual float x() const;
        virtual float y() const;
        virtual float z() const;

        void x(float val);
        void y(float val);
        void z(float val);

    protected:
        float values[3];
    };
}

#include <yaml-cpp/yaml.h>
namespace YAML {
    template<>
    class convert<maths::Vector> {
    public:
        static bool decode(const Node &node, maths::Vector &rhs) {
            auto x = node["x"], y = node["y"], z = node["z"];

            if (!x || !y || !z) {
                return false;
            }

            rhs.x(x.as<float>());
            rhs.y(y.as<float>());
            rhs.z(z.as<float>());
            return true;
        }
    };
}

#endif // VECTOR_HPP