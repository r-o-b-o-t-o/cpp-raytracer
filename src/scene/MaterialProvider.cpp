#include "scene/MaterialProvider.hpp"
#include "scene/Object.hpp"

namespace scene {
    MaterialProvider::MaterialProvider() {
        this->materials[0] = Material(
            Color(1.0f, 1.0f, 1.0f),
            Color(0.25f, 0.25f, 0.25f),
            Color(0.75f, 0.75f, 0.75f),
            3.0f
        );
        this->type = HOMOGENEOUS;
    }

    MaterialProvider &MaterialProvider::operator=(const MaterialProvider &mp) {
        if(&mp == this) {
            return *this;
        }

        this->type = mp.type;

        int i = 0;
        for (auto &m : this->materials) {
            m = mp.materials[i];
            ++i;
        }

        return *this;
    }

    const scene::Material &MaterialProvider::getMaterial(const Object &obj, const maths::Point &point) const {
        if (this->type == DUAL_CHECKERBOARD) {
            auto coords = obj.getMaterialCoordinates(point);
            int x = (int)(coords.x() * 2.0f);
            int y = (int)(coords.y() * 2.0f);
            int idx = x % 2 == (y + 1) % 2;
            return this->materials[idx];
        } else if (this->type == DUAL_STRIPES) {
            auto coords = obj.getMaterialCoordinates(point);
            int idx = (coords.x() > 0.25f && coords.x() <= 0.5f) || (coords.x() > 0.75 && coords.x() <= 1.0f);
            return this->materials[idx];
        }
        return this->materials[0];
    }

    void MaterialProvider::setMaterial(const int idx, const Material &material) {
        this->materials[idx] = material;
    }

    void MaterialProvider::setType(int type) {
        this->type = type;
    }
}
