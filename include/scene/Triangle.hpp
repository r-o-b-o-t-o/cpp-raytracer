#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Plane.hpp"

namespace scene {
    class Triangle : public Plane {
    public:
        Triangle() = default;
        explicit Triangle(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Point getTextureCoordinates(const maths::Point &p) const override;
        maths::Point getMaterialCoordinates(const maths::Point &p) const override;
        bool PointInTriangle (maths::Point &pt, maths::Point &v1, maths::Point &v2, maths::Point &v3) const;
        float sign (maths::Point &p1, maths::Point &p2, maths::Point &p3) const;
    };
}

#endif // TRIANGLE_HPP