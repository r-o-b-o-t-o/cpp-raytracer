#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Entity.hpp"

namespace Scene {
    class Object : public Entity {
    public:
        Object(const Math::Point&);
        virtual bool intersect(const Math::Ray &ray, Math::Point &impact) const = 0;
        virtual Math::Ray getNormal(const Math::Point &impact, const Math::Point &observator) const = 0;
    };
}

#endif // OBJECT_HPP