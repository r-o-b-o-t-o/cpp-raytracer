#include "scene/Object.hpp"

namespace scene {
    Object::Object(const maths::Point &point) : Entity(point) {

    }

    scene::Material Object::getMaterial(const maths::Point &point) const {
        return scene::Material();
    }
}