#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

namespace scene {
    class Sphere : public Object {
    public:
        Sphere() = default;
        explicit Sphere(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const override;
    };
}

#endif // SPHERE_HPP