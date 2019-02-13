#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"

namespace Scene {
    class Light : public Entity {
    public:
        explicit Light(const Math::Point &point);

    private:
        Math::Ray getNormal(const Math::Point &impact, const Math::Point &observator) const override;
    };
}

#endif // LIGHT_HPP