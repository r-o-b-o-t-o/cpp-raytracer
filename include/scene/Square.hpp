#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Plane.hpp"

namespace scene {
    class Square : public Plane {
    public:
        Square(const maths::Point &point);
        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
    };
}

#endif // SQUARE_HPP