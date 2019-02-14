#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene/Entity.hpp"
#include "math/Ray.hpp"

namespace Scene {
    class Camera : public Entity {
    public:
        explicit Camera(Math::Point);

        Math::Ray getRay(float x, float y) const;
        void setFocal(float);
        float getFocal() const override;

    };
}

#endif // CAMERA_HPP