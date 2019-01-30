#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "Point.hpp"

namespace Math {
    class Vector : public Point {
    public:
        Vector();
        Vector(float x, float y, float z);
        Vector(const Vector &v);
        explicit Vector(const Point &p);

        float norm() const;
        void normalize();
        Vector normalized() const;

        friend std::ostream &operator<<(std::ostream &s, const Vector &v);
    };
}

#endif // VECTOR_HPP
