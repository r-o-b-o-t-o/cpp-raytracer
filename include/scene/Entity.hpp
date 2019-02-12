#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "math/Point.hpp"
#include "math/Ray.hpp"
#include "math/Matrix.hpp"

namespace Scene {
    class Entity {
        public:
            void setPos(Math::Point);
            void setPos(float, float, float);

            Math::Point getPos();
            Entity();
            Entity(Math::Point);
        protected:
            Math::Point pos;
            Math::Matrix trans;
            Math::Matrix transInv;

            void translate(float x, float y, float z); // effectue une translation de vecteur (x,y,z)
            void rotateX(float deg); // effectue une rotation sur l'axe X, de deg radians
            void rotateY(float deg); // effectue une rotation sur l'axe Y, de deg radians
            void rotateZ(float deg); // effectue une rotation sur l'axe Z, de deg radians
            void scale(float factor); // effectue un redimensionnement de facteur factor

            template<typename T>
            T localToGlobal(T& in){
                return transInv * in;
            }
            template <Math::Ray&>
            Math::Ray localToGlobal(const Math::Ray& r){
                Math::Ray t = Math::Ray(this->localToGlobal(r.getOrigin()), this->localToGlobal(r.getVector()));
                return t;
            }

            template<typename T>
            T globalToLocal(T& in){
                return trans * in;
            }
            template <Math::Ray&>
            Math::Ray globalToLocal(const Math::Ray& r){
                Math::Ray t = Math::Ray(this->globalToLocal(r.getOrigin()), this->globalToLocal(r.getVector()));
                return t;
            }
    };
}

#endif // ENTITY_HPP