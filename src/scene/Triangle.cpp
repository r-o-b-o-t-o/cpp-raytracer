#include "scene/Triangle.hpp"
#include <math.h>

namespace scene {
    Triangle::Triangle(const maths::Point &point) : Plane(point) {

    }

    bool Triangle::intersect(const maths::Ray &ray, maths::Point &impact) const {
        maths::Ray rayon = this->globalToLocal(ray);
        auto t = -(rayon.getOrigin().z() / rayon.getVector().z());

        if (t < 0) {
            return false;
        }
        impact = rayon.getOrigin() + t * rayon.getVector();
        maths::Point pa = maths::Point(this->pos[0], this->pos[1]+sqrt(3)/3, 0);
        maths::Point pb = maths::Point(this->pos[0]-0.5f, this->pos[1]-sqrt(3)/6, 0);
        maths::Point pc = maths::Point(this->pos[0]+0.5f, this->pos[1]-sqrt(3)/6, 0);
        if (!PointInTriangle(impact, pa, pb, pc)) {
            return false;
        }
        impact = this->localToGlobal(impact) + this->getNormal(impact, ray.getOrigin()).getVector() * 0.0005f;

        return true;
    }

    float Triangle::sign (maths::Point &p1, maths::Point &p2, maths::Point &p3) const {
        return (p1[0] - p3[0]) * (p2[1] - p3[1]) - (p2[0] - p3[0]) * (p1[1] - p3[1]);
    }

    bool Triangle::PointInTriangle (maths::Point &pt, maths::Point &v1, maths::Point &v2, maths::Point &v3) const {
        float d1, d2, d3;
        bool has_neg, has_pos;

        d1 = sign(pt, v1, v2);
        d2 = sign(pt, v2, v3);
        d3 = sign(pt, v3, v1);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }

    maths::Point Triangle::getTextureCoordinates(const maths::Point &point) const {
        auto p = globalToLocal(point);
        maths::Point textCoords(p.x() / 2.0f + 0.5f, p.y() / 2.0f + 0.5f, 0.0f);
        return textCoords;
    }

    maths::Point Triangle::getMaterialCoordinates(const maths::Point &point) const {
        return Plane::getTextureCoordinates(point);
    }
}
