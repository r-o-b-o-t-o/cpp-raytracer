#include "scene/Color.hpp"

#include <algorithm>

namespace Scene {
    Color::Color(float r, float g, float b)
            : _r(r), _g(g), _b(b) {

    }

    float Color::r() const {
        return this->_r;
    }

    float Color::g() const {
        return this->_g;
    }

    float Color::b() const {
        return this->_b;
    }

    void Color::r(float r) {
        this->_r = r;
    }

    void Color::g(float g) {
        this->_g = g;
    }

    void Color::b(float b) {
        this->_b = b;
    }

    Color Color::mul(const Color &c) {
        return Color(this->r() * c.r(), this->g() * c.g(), this->b() * c.b());
    }
}
