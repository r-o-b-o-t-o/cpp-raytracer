#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

namespace scene {
    class Plane : public Object {
    public:
        explicit Plane(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const override;
    };
}

#endif // PLANE_HPP