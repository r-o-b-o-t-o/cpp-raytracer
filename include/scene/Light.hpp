#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"

namespace Scene {
    class Light : public Entity {
        public:
        Light(Math::Point);
    };
}

#endif // LIGHT_HPP