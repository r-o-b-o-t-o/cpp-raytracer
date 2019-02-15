#ifndef HVECTOR_HPP
#define HVECTOR_HPP

#include "Vector.hpp"

namespace maths {
    class HVector : public Vector {
    public:
        HVector();
        HVector(float x, float y, float z);
        HVector(float x, float y, float z, float w);
        HVector(const HVector &v);
        HVector(const HVector &v, float w);
        explicit HVector(const Vector &v);
        HVector(const Vector &v, float w);

        float x() const override;
        float y() const override;
        float z() const override;
        float w() const;

    protected:
        float _w;
    };
}

#endif // HVECTOR_HPP
