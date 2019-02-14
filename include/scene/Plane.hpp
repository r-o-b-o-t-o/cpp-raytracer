#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

namespace Scene {
    class Plane : public Object {
    public:
        Plane(Math::Point point);
        bool intersect(const Math::Ray &ray, Math::Point &impact) const override;
        Math::Ray getNormal(const Math::Point &impact, const Math::Point &observator) const override;
    };
}

#endif // PLANE_HPP