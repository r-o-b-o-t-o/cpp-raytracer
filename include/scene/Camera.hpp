#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene/Entity.hpp"
#include "maths/Ray.hpp"
#include "scene/Color.hpp"
#include "scene/Object.hpp"
#include "scene/Scene.hpp"

namespace scene {
    class Camera : public Entity {
    public:
        explicit Camera(maths::Point);

        maths::Ray getRay(float x, float y) const;
        void setFocal(float);
        float getFocal() const;
        scene::Color getImpactColor(const maths::Ray& ray, const scene::Object& obj, const maths::Point& impact, const scene::Scene& sc)const;

    protected:
        float focal;
    };
}

#endif // CAMERA_HPP