#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "scene/Color.hpp"

namespace scene {
    class Material {
    public:

    Material();

    Color getKa() const;
    Color getKd() const;
    Color getKs() const;
    int getShininess() const;

    void setShininess(int);
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