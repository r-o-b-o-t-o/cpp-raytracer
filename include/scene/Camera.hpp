#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene/Entity.hpp"
#include "maths/Ray.hpp"
#include "scene/Color.hpp"
#include "scene/Object.hpp"

namespace scene {
    class Scene; // Forward declaration

    class Camera : public Entity {
    public:
        Camera();
        explicit Camera(maths::Point);

        maths::Ray getRay(float x, float y) const;
        void setFocal(float);
        float getFocal() const;
        scene::Color getImpactColor(const maths::Ray &ray, const scene::Object &obj, const maths::Point &impact, const Scene &sc) const;

    protected:
        float focal;
    };
}

#include <yaml-cpp/yaml.h>
namespace YAML {
    template<>
    class convert<scene::Camera> {
    public:
        static bool decode(const Node &node, scene::Camera &rhs) {
            rhs.fromYaml(node);
            auto focal = node["focal"];

            if (focal) {
                rhs.setFocal(focal.as<float>());
            }
            return true;
        }
    };
}

#endif // CAMERA_HPP