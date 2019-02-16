#include <cmath>
#include "scene/Entity.hpp"

namespace scene {
    Entity::Entity()
            : pos(maths::Point()),
              trans(maths::Matrix()),
              transInv(maths::Matrix()) {
    }

    Entity::Entity(const maths::Point &point) : Entity() {
        this->translate(maths::Vector(point));
    }

    void Entity::setPos(const maths::Point &p) {
        this->pos = p;
        this->translate(maths::Vector(p));
    }

    void Entity::setPos(float x, float y, float z) {
        this->setPos(maths::Point(x, y, z));
    }

    const maths::Point &Entity::getPos() const {
        return this->pos;
    }

    // effectue une translation de vecteur v
    void Entity::translate(const maths::Vector &v) {
        this->translate(v.x(), v.y(), v.z());
    }

    // effectue une translation de vecteur (x,y,z)
    void Entity::translate(float x, float y, float z) {
        maths::Matrix mat = maths::Matrix();

        mat(0, 3) = x;
        mat(1, 3) = y;
        mat(2, 3) = z;
        this->trans = mat * this->trans;

        this->transInv = this->trans.inverse();
    }

    void Entity::rotate(const maths::Vector &v) {
        this->rotateX(v.x());
        this->rotateY(v.y());
        this->rotateZ(v.z());
    }

    // effectue une rotation sur l'axe X, de deg radians
    void Entity::rotateX(float deg) {
        maths::Matrix mat = maths::Matrix();

        mat(2, 1) = sinf(deg);
        mat(2, 2) = cosf(deg);
        mat(1, 1) = cosf(deg);
        mat(1, 2) = -sinf(deg);

        this->trans = mat * this->trans;
        this->transInv = this->trans.inverse();
    }

    // effectue une rotation sur l'axe Y, de deg radians
    void Entity::rotateY(float deg) {
        maths::Matrix mat = maths::Matrix();

        mat(0, 2) = sinf(deg);
        mat(2, 2) = cosf(deg);
        mat(0, 0) = cosf(deg);
        mat(2, 0) = -sinf(deg);

        this->trans = mat * this->trans;
        this->transInv = this->trans.inverse();
    }

    // effectue une rotation sur l'axe Z, de deg radians
    void Entity::rotateZ(float deg) {
        maths::Matrix mat = maths::Matrix();

        mat(1, 0) = sinf(deg);
        mat(0, 0) = cosf(deg);
        mat(1, 1) = cosf(deg);
        mat(0, 1) = -sinf(deg);

        this->trans = mat * this->trans;
        this->transInv = this->trans.inverse();
    }

    void Entity::scale(const maths::Vector &v) {
        this->scale(v.x(), v.y(), v.z());
    }

    // effectue un redimensionnement de facteurs (x,y,z)
    void Entity::scale(float x, float y, float z) {
        maths::Matrix mat = maths::Matrix(3, 3);

        mat(0, 0) = x;
        mat(1, 1) = y;
        mat(2, 2) = z;

        this->trans = mat * this->trans;
        this->transInv = this->trans.inverse();
    }

    // effectue un redimensionnement de facteur factor
    void Entity::scale(float factor) {
        maths::Matrix mat = maths::Matrix(3, 3);

        mat(0, 0) = factor;
        mat(1, 1) = factor;
        mat(2, 2) = factor;

        this->trans = mat * this->trans;
        this->transInv = this->trans.inverse();
    }

    void Entity::fromYaml(const YAML::Node &node) {
        auto pos = node["position"];
        auto rot = node["rotation"];
        auto scale = node["scale"];

        if (scale) {
            if (scale.IsScalar()) {
                this->scale(scale.as<float>());
            } else {
                this->scale(scale.as<maths::Vector>());
            }
        }

        if (rot) {
            auto v = rot.as<maths::Vector>();
            this->rotate(v);
        }

        if (pos) {
            auto p = pos.as<maths::Point>();
            this->setPos(p);
        }
    }
}

