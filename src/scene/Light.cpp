#include "scene/Light.hpp"

namespace scene {
    Light::Light() : Light(maths::Point()) {

    }

    Light::Light(const maths::Point &point)
            : Entity(point),
              diffuse(255.0f, 255.0f, 255.0f),
              specular(255.0f, 255.0f, 255.0f) {

    }

    maths::Ray Light::getRayToLight(const maths::Point &p) const {
        return maths::Ray(p, this->getVectorToLight(p));
    }

    maths::Ray Light::getRayFromLight(const maths::Point &p) const {
        return maths::Ray(this->pos, this->getVectorFromLight(p));
    }

    maths::Vector Light::getVectorToLight(const maths::Point &p) const {
        return maths::Vector(this->pos - p);
    }

    maths::Vector Light::getVectorFromLight(const maths::Point &p) const {
        return maths::Vector(p - this->pos);
    }

    Color Light::getDiffuseColor() const {
        return this->diffuse;
    }

    void Light::setDiffuseColor(const Color &diffuse) {
        this->diffuse = diffuse;
    }

    Color Light::getSpecularColor() const {
        return this->specular;
    }

    void Light::setSpecularColor(const Color &specular) {
        this->specular = specular;
    }
}
