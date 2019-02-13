#ifndef PLANE_HPP
#define PLANE_HPP

#include "Object.hpp"

namespace Scene {
    class Plane : public Object {
    public:
        bool intersect(const Math::Ray &ray, Math::Point &impact) const override;
    };
}

#endif // PLANE_HPP