#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

namespace scene {
    class Plane : public Object {
    public:
        Plane() = default;
        explicit Plane(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const override;
        maths::Point getTextureCoordinates(const maths::Point &p) const override;
        maths::Point getMaterialCoordinates(const maths::Point &p) const override;
    };
}

#endif // PLANE_HPP