#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Entity.hpp"
#include "scene/MaterialProvider.hpp"

namespace scene {
    class Object : public Entity {
    public:
        Object();
        explicit Object(const maths::Point&);

        const scene::Material &getMaterial(const maths::Point &point) const;
        virtual maths::Point getTextureCoordinates(const maths::Point& p) const = 0;
        virtual maths::Point getMaterialCoordinates(const maths::Point& p) const = 0;
        virtual bool intersect(const maths::Ray &ray, maths::Point &impact) const = 0;
        virtual maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const = 0;

    protected:
        scene::MaterialProvider materialProvider;

    public:
        void fromYaml(const YAML::Node &node) override;
    };
}

#endif // OBJECT_HPP