#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"
#include "Color.hpp"

namespace Scene {
    class Light : public Entity {
    public:
        explicit Light(const Math::Point &point);

        Math::Ray getRayToLight(const Math::Point &p) const;
        Math::Ray getRayFromLight(const Math::Point &p) const;
        Math::Vector getVectorToLight(const Math::Point &p) const;
        Math::Vector getVectorFromLight(const Math::Point &p) const;

        const Color &getDiffuseColor() const;
        void setDiffuseColor(const Color &diffuse);
        const Color &getSpecularColor() const;
        void setSpecularColor(const Color &specular);

    protected:
        Color diffuse;
        Color specular;
    };
}

#endif // LIGHT_HPP