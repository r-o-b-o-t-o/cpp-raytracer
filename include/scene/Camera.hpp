#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scene/Entity.hpp"
#include "math/Ray.hpp"

namespace Scene {
    class Camera : public Entity {
        private:
        float focal;
        public:
        Math::Ray getRay(float x, float y) const;
        void getFocal(float);
        float setFocal();
        Camera(Math::Point);
    };
}

#endif // CAMERA_HPP