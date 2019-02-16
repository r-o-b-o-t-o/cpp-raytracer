#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Entity.hpp"
#include "Color.hpp"

namespace scene {
    class Light : public Entity {
    public:
        Light();
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

#include <yaml-cpp/yaml.h>
namespace YAML {
    template<>
    class convert<scene::Light> {
    public:
        static bool decode(const Node &node, scene::Light &rhs) {
            rhs.fromYaml(node);
            auto diffuse = node["diffuse"];
            auto specular = node["specular"];

            if (diffuse) {
                rhs.setDiffuseColor(diffuse.as<scene::Color>());
            }
            if (specular) {
                rhs.setSpecularColor(specular.as<scene::Color>());
            }
            return true;
        }
    };
}

#endif // LIGHT_HPP