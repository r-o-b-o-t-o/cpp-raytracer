#ifndef CUBE_HPP
#define CUBE_HPP

#include "Square.hpp"

namespace Scene {
    class Cube : public Square {
    public:
        Cube(const Math::Point &point);

    };
}

#endif // CUBE_HPP