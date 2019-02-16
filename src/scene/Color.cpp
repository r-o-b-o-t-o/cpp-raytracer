#include "scene/Color.hpp"

#include <algorithm>

namespace scene {
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

    Color Color::operator*(float f) const {
        Color c(*this);
        c *= f;
        return c;
    }

    Color &Color::operator*=(float f) {
        this->_r *= f;
        this->_g *= f;
        this->_b *= f;
        this->clamp();
        return *this;
    }

    void Color::clamp() {
        this->_r = std::max(0.0f, std::min(1.0f, this->_r));
        this->_g = std::max(0.0f, std::min(1.0f, this->_g));
        this->_b = std::max(0.0f, std::min(1.0f, this->_b));
    }

    Color operator*(float f, const Color &c) {
        return c * f;
    }

    Color Color::operator+(const Color &c) const {
        Color res(*this);
        res += c;
        return res;
    }

    Color &Color::operator+=(const Color &c) {
        this->_r += c._r;
        this->_g += c._g;
        this->_b += c._b;
        this->clamp();
        return *this;
    }

    std::ostream &operator<<(std::ostream &s, const Color &c) {
        s << "Color (R: " << c.r() << ", G: " << c.g() << ", B: " << c.b() << ")";
        return s;
    }
}
