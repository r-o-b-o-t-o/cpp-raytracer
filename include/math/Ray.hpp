#ifndef RAY_HPP
#define RAY_HPP

#include "Vector.hpp"

namespace Math {
    class Ray {
    public:
        Ray() = default;
        Ray(float ox, float oy, float oz, float vx, float vy, float vz);
        Ray(Point o, Vector v);
        Ray(const Ray &r) = default;
        void normalize();
        Ray normalized() const;

        const Point &getOrigin() const;
        void setOrigin(const Point &p);
        const Vector &getVector() const;
        void setVector(const Vector &v);

    protected:
        Point origin;
        Vector vector;
    };
}

#endif // RAY_HPP
