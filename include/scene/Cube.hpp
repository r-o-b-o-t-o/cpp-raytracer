#ifndef CUBE_HPP
#define CUBE_HPP

#include "Square.hpp"

namespace scene {
    class Cube : public Object {
    public:
        explicit Cube(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Ray getNormal(const maths::Point &impact, const maths::Point &observator) const override;
    };
}

#endif // CUBE_HPP