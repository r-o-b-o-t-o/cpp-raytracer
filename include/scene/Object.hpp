#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Entity.hpp"
#include "scene/Material.hpp"

namespace scene {
    class Object : public Entity {
    public:
        explicit Object(const maths::Point&);

        scene::Material getMaterial(const maths::Point &point) const;
        virtual bool intersect(const maths::Ray &ray, maths::Point &impact) const = 0;
        virtual maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const = 0;
    };
}

#endif // OBJECT_HPP