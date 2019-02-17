#ifndef MATERIAL_PROVIDER_HPP
#define MATERIAL_PROVIDER_HPP

#include "maths/Point.hpp"
#include "scene/Material.hpp"

namespace scene {
    class Object;

    class MaterialProvider {
    public:
        MaterialProvider();
        MaterialProvider &operator=(const MaterialProvider &mp);

        const Material &getMaterial(const Object &obj, const maths::Point &point) const;
        void setMaterial(int idx, const Material &material);
        void setType(int type);

        const int HOMOGENEOUS = 1;
        const int DUAL_STRIPES = 2;
        const int DUAL_CHECKERBOARD = 3;

    protected:
        int type;
        Material materials[2];
    };
}

#include <yaml-cpp/yaml.h>
namespace YAML {
    template<>
    class convert<scene::MaterialProvider> {
    public:
        static bool decode(const Node &node, scene::MaterialProvider &rhs) {
            auto material = node["material"];
            auto materials = node["materials"];

            if (material) {
                rhs.setMaterial(0, material.as<scene::Material>());
                rhs.setType(rhs.HOMOGENEOUS);
            } else if (materials) {
                rhs.setType(rhs.DUAL_CHECKERBOARD);

                int i = 0;
                for (auto it = materials.begin(); it != materials.end(); ++it) {
                    const YAML::Node &mat = *it;
                    if (mat["type"]) {
                        std::string type = mat["type"].as<std::string>();
                        if (type == "checkerboard") rhs.setType(rhs.DUAL_CHECKERBOARD);
                        else if (type == "stripes") rhs.setType(rhs.DUAL_STRIPES);
                    } else {
                        rhs.setMaterial(i, mat.as<scene::Material>());
                        ++i;
                    }
                }
            }
            return true;
        }
    };
}

#endif // MATERIAL_PROVIDER_HPP