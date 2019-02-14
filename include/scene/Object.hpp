#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Entity.hpp"

namespace Scene {
    class Object : public Entity {
    public:
        Object(Math::Point);
        virtual bool intersect(const Math::Ray &ray, Math::Point &impact) const = 0;
    };
}

#endif // OBJECT_HPP