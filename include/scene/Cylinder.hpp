#ifndef CYLINDRE_HPP
#define CYLINDRE_HPP

#include "Object.hpp"

namespace scene {
    class Cylinder : public Object {
    public:
        Cylinder() = default;
        explicit Cylinder(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const override;
        maths::Point getTextureCoordinates(const maths::Point &p) const override;
        maths::Point getMaterialCoordinates(const maths::Point &p) const override;
    };
}

#endif // CYLINDRE_HPP