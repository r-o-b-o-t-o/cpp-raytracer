#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "maths/Point.hpp"
#include "maths/Ray.hpp"
#include "maths/Matrix.hpp"

namespace scene {
    class Entity {
    public:
        void setPos(maths::Point);
        void setPos(float, float, float);

        maths::Point getPos();
        Entity();
        explicit Entity(maths::Point);
        virtual ~Entity() = 0;

        void translate(float x, float y, float z); // effectue une translation de vecteur (x,y,z)
        void rotateX(float deg); // effectue une rotation sur l'axe X, de deg radians
        void rotateY(float deg); // effectue une rotation sur l'axe Y, de deg radians
        void rotateZ(float deg); // effectue une rotation sur l'axe Z, de deg radians
        void scale(float factor); // effectue un redimensionnement de facteur factor

    protected:
        maths::Point pos;
        maths::Matrix trans;
        maths::Matrix transInv;

        template<typename T>
        T localToGlobal(const T &in) const {
            return trans * in;
        }

        maths::Ray localToGlobal(const maths::Ray &r) const {
            maths::Ray t = maths::Ray(this->localToGlobal(r.getOrigin()), this->localToGlobal(r.getVector()));
            return t;
        }

        template<typename T>
        T globalToLocal(const T &in) const {
            return transInv * in;
        }

        maths::Ray globalToLocal(const maths::Ray &r) const {
            maths::Ray t = maths::Ray(this->globalToLocal(r.getOrigin()), this->globalToLocal(r.getVector()));
            return t;
        }
    };
}

inline scene::Entity::~Entity() = default;

#endif // ENTITY_HPP