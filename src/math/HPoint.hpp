#ifndef HPOINT_HPP
#define HPOINT_HPP

#include "Point.hpp"

namespace Math {
    class HPoint : public Point {
    public:
        HPoint();
        HPoint(float x, float y, float z);
        HPoint(float x, float y, float z, float w);
        HPoint(const HPoint &p);
        HPoint(const HPoint &p, float w);
        explicit HPoint(const Point &p);
        HPoint(const Point &p, float w);

        float x() const override;
        float y() const override;
        float z() const override;
        float w() const;

    protected:
        float _w;
    };
}

#endif // HPOINT_HPP
