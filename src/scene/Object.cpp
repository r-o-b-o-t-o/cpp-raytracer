#include "scene/Object.hpp"

namespace scene {

    Object::Object(const maths::Point &point): Entity(point){
        
    }


    scene::Material getMaterial(const maths::Point &point) {
        return scene::Material();   
    }
}