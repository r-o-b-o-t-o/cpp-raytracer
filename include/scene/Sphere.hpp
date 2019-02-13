#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

namespace Scene {
    class Sphere : public Object {
    public:
        bool intersect(const Math::Ray &ray, Math::Point &impact) const override;
        Math::Ray getNormal(const Math::Point &impact, const Math::Point &observator) const override;
    };
}

#endif // SPHERE_HPP