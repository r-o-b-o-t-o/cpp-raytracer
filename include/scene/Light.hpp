#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"
#include "Color.hpp"

namespace scene {
    class Light : public Entity {
    public:
        explicit Light(const maths::Point &point);

        maths::Ray getRayToLight(const maths::Point &p) const;
        maths::Ray getRayFromLight(const maths::Point &p) const;
        maths::Vector getVectorToLight(const maths::Point &p) const;
        maths::Vector getVectorFromLight(const maths::Point &p) const;

        Color getDiffuseColor() const;
        void setDiffuseColor(const Color &diffuse);
        Color getSpecularColor() const;
        void setSpecularColor(const Color &specular);

    protected:
        Color diffuse;
        Color specular;
    };
}

#endif // LIGHT_HPP