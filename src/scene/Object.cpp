#include "scene/Object.hpp"

namespace scene {
    Object::Object() : Entity() {
        this->material = Material(
            Color(1.0f, 1.0f, 1.0f),
            Color(0.25f, 0.25f, 0.25f),
            Color(0.75f, 0.75f, 0.75f),
            3.0f
        );
    }

    Object::Object(const maths::Point &point) : Entity(point) {

    }

    const scene::Material &Object::getMaterial(const maths::Point &point) const {
        return this->material;
    }

    void Object::fromYaml(const YAML::Node &node) {
        Entity::fromYaml(node);

        auto material = node["material"];

        if (material) {
            this->material = material.as<Material>();
        }
    }
}
