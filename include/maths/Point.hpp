#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>
#include <yaml-cpp/yaml.h>

namespace maths {
    class Vector; // Forward declaration

    class Point {
    public:
        Point();
        Point(float x, float y, float z);
        Point(const Point &p);
        explicit Point(const Vector &v);
        explicit operator Vector() const;
        Point &operator=(const Point &p);
        Point &operator=(const Vector &v);

        float dot(const Point &other);

        float &operator[](int);
        const float &operator[](int) const;

        friend std::ostream &operator<<(std::ostream &s, const Point &p);

        Point operator+(const Point &other) const;
        Point &operator+=(const Point &rhs);
        Point operator+(const Vector &other) const;
        Point &operator+=(const Vector &rhs);
        Point operator-(const Point &other) const;
        Point &operator-=(const Point &rhs);
        Point operator-(const Vector &other) const;
        Point &operator-=(const Vector &rhs);
        Point operator-() const;
        Point operator*(const float &mul) const;
        Point &operator*=(const float &mul);
        Point operator/(const float &mul) const;
        Point &operator/=(const float &mul);
        friend Point operator*(const float &mul, const Point &p);

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

namespace YAML {
    template<>
    class convert<maths::Point> {
    public:
        static bool decode(const Node &node, maths::Point &rhs) {
            if (node["x"].IsNull() || node["y"].IsNull() || node["z"].IsNull()) {
                return false;
            }

            rhs.x(node["x"].as<float>());
            rhs.y(node["y"].as<float>());
            rhs.z(node["z"].as<float>());
            return true;
        }
    };
}

#endif // POINT_HPP