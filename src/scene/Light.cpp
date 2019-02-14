#include "scene/Light.hpp"

namespace Scene {
    Light::Light(const Math::Point &point) : Entity(point) {

    }

    Math::Ray Light::getRayToLight(const Math::Point &p) const {
        return Math::Ray(p, this->getVectorToLight(p));
    }

    Math::Ray Light::getRayFromLight(const Math::Point &p) const {
        return Math::Ray(this->pos, this->getVectorFromLight(p));
    }

    Math::Vector Light::getVectorToLight(const Math::Point &p) const {
        return Math::Vector(this->pos - p);
    }

    Math::Vector Light::getVectorFromLight(const Math::Point &p) const {
        return Math::Vector(p - this->pos);
    }

    const Color &Light::getDiffuseColor() const {
        return this->diffuse;
    }

    void Light::setDiffuseColor(const Color &diffuse) {
        this->diffuse = diffuse;
    }

    const Color &Light::getSpecularColor() const {
        return this->specular;
    }

    void Light::setSpecularColor(const Color &specular) {
        this->specular = specular;
    }
}
