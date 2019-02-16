#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene/Entity.hpp"
#include "maths/Ray.hpp"
#include "scene/Color.hpp"
#include "scene/Object.hpp"
#include <algorithm>

namespace scene {
    class Scene; // Forward declaration

    class Camera : public Entity {
    public:
        Camera();
        explicit Camera(maths::Point);

        maths::Ray getRay(float x, float y) const;
        void setFocal(float);
        float getFocal() const;
        void setWidth(float);
        float getWidth() const;
        void setHeight(float);
        float getHeight() const;
        void setSize(float);
        float getSize() const;
        scene::Color getImpactColor(const maths::Ray &ray, const scene::Object &obj, const maths::Point &impact, const Scene &sc) const;

    protected:
        float focal;
        float size;
        float height;
        float width;
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
            auto resolution = node["resolution"];

            if (focal) {
                rhs.setFocal(focal.as<float>());
            }
            if (resolution)
            {
                auto width = resolution["width"];
                auto height = resolution["height"];
                if (width) {
                    rhs.setWidth(static_cast<float>(width.as<int>()));
                }
                if (height) {
                    rhs.setHeight(static_cast<float>(height.as<int>()));
                }
                if (width && height) {
                    rhs.setSize(static_cast<float>(std::min(width.as<int>(), height.as<int>())));
                }
            }
            return true;
        }
    };
}

#endif // CAMERA_HPP