#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "scene/Color.hpp"

namespace scene {
    class Material {
    public:
        Material();
        Material(Color ka, Color kd, Color ks);
        Material(Color ka, Color kd, Color ks, float shininess);

        Color getKa() const;
        Color getKd() const;
        Color getKs() const;
        float getShininess() const;

        void setShininess(float s);
        void setKa(Color);
        void setKd(Color);
        void setKs(Color);

    private:
        Color ka;
        Color kd;
        Color ks;
        float shininess;
    };
}

#include <yaml-cpp/yaml.h>
namespace YAML {
    template<>
    class convert<scene::Material> {
    public:
        static bool decode(const Node &node, scene::Material &rhs) {
            auto ambiant = node["ambiant"];
            auto diffuse = node["diffuse"];
            auto specular = node["specular"];
            auto shininess = node["shininess"];

            if (ambiant) {
                rhs.setKa(ambiant.as<scene::Color>());
            }
            if (diffuse) {
                rhs.setKd(diffuse.as<scene::Color>());
            }
            if (specular) {
                rhs.setKs(specular.as<scene::Color>());
            }
            if (shininess) {
                rhs.setShininess(shininess.as<float>());
            }
            return true;
        }
    };
}

#endif // MATERIAL_HPP