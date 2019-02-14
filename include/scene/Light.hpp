#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"

namespace Scene {
    class Light : public Entity {
    public:
        explicit Light(const Math::Point &point);

    private:
    };
}

#endif // LIGHT_HPP