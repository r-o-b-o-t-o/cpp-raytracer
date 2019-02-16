#include "scene/Object.hpp"

namespace scene {
    Object::Object() : Entity() {

    }

    Object::Object(const maths::Point &point) : Entity(point) {

    }

    scene::Material Object::getMaterial(const maths::Point &point) const {
        return Material(
            Color(0.1f, 0.1f, 0.5f),
            Color(0.25f, 0.25f, 0.25f),
            Color(0.75f, 0.75f, 0.75f),
            3.0f
        );
    }
}