#ifndef CUBE_HPP
#define CUBE_HPP

#include "Square.hpp"

namespace scene {
    class Cube : public Object {
    public:
        Cube() = default;
        explicit Cube(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        float intersectsSide(const maths::Ray &ray, int dim, float offset) const;
        maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const override;
        maths::Point getTextureCoordinates(const maths::Point &p) const override;
        maths::Point getMaterialCoordinates(const maths::Point &p) const override;
    };
}

#endif // CUBE_HPP