#include "scene/Material.hpp"

namespace scene {
    Material::Material()
            : ka(scene::Color()),
              kd(scene::Color()),
              ks(scene::Color()),
              shininess(3.0f) {

    }

    Material::Material(Color ka, Color kd, Color ks)
            : ka(ka),
              kd(kd),
              ks(ks),
              shininess(3.0f) {

    }

    Material::Material(Color ka, Color kd, Color ks, float shininess) : Material(ka, kd, ks) {
        this->shininess = shininess;
    }

    scene::Color Material::getKa() const {
        return this->ka;
    }

    scene::Color Material::getKd() const {
        return this->kd;
    }

    scene::Color Material::getKs() const {
        return this->ks;
    }

    float Material::getShininess() const {
        return this->shininess;
    }

    void Material::setShininess(float s) {
        this->shininess = s;
    }

    void Material::setKa(scene::Color col) {
        this->ka = col;
    }

    void Material::setKd(scene::Color col) {
        this->kd = col;
    }

    void Material::setKs(scene::Color col) {
        this->ks = col;
    }
}
