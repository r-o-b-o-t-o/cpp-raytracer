#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Plane.hpp"

namespace Scene {
    class Square : public Plane {
    public:
        Square(const Math::Point &point);
        bool intersect(const Math::Ray &ray, Math::Point &impact) const override;
    };
}

#endif // SQUARE_HPP