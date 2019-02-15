#ifndef CUBE_HPP
#define CUBE_HPP

#include "Square.hpp"

namespace scene {
    class Cube : public Square {
    public:
        Cube(const maths::Point &point);

    };
}

#endif // CUBE_HPP