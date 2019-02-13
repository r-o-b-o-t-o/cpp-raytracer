#include "scene/Light.hpp"

namespace Scene {
    Light::Light(const Math::Point &point) : Entity(point) {

    }

    Math::Ray Light::getNormal(const Math::Point &impact, const Math::Point &observator) const {
        return Math::Ray();
    }
}
