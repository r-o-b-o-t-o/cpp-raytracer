#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Plane.hpp"

namespace scene {
    class Square : public Plane {
    public:
        Square() = default;
        explicit Square(const maths::Point &point);

        bool intersect(const maths::Ray &ray, maths::Point &impact) const override;
        maths::Point getTextureCoordinates(const maths::Point &p) const override;
        maths::Point getMaterialCoordinates(const maths::Point &p) const override;
    };
}

#endif // SQUARE_HPP