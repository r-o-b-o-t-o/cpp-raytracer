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
#endif // MATERIAL_HPP