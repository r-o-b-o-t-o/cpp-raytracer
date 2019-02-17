#include "scene/Object.hpp"

namespace scene {
    Object::Object() : Entity() {

    }

    Object::Object(const maths::Point &point) : Entity(point) {

    }

    const scene::Material &Object::getMaterial(const maths::Point &point) const {
        return this->materialProvider.getMaterial(*this, point);
    }

    void Object::fromYaml(const YAML::Node &node) {
        Entity::fromYaml(node);
        this->materialProvider = node.as<MaterialProvider>();
    }
}
