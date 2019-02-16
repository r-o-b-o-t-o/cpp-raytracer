#ifndef COLOR_HPP
#define COLOR_HPP

#include <ostream>

namespace scene {
    class Color {
    public:
        Color() = default;
        Color(float r, float g, float b);
        Color(const Color &c) = default;

        float r() const;
        float g() const;
        float b() const;

        void r(float r);
        void g(float g);
        void b(float b);

        Color mul(const Color &c);
        Color operator*(float f) const;
        Color &operator*=(float f);
        friend Color operator*(float f, const Color &c);
        Color operator+(const Color &c) const;
        Color &operator+=(const Color &c);

        void clamp();

        friend std::ostream &operator<<(std::ostream &s, const Color &c);

    protected:
        float _r;
        float _g;
        float _b;
    };
}

#include <yaml-cpp/yaml.h>
namespace YAML {
    template<>
    class convert<scene::Color> {
    public:
        static bool decode(const Node &node, scene::Color &rhs) {
            auto r = node["r"], g = node["g"], b = node["b"];

            if (!r || !g || !b) {
                return false;
            }

            rhs.r(r.as<float>() / 255.0f);
            rhs.g(g.as<float>() / 255.0f);
            rhs.b(b.as<float>() / 255.0f);
            return true;
        }
    };
}

#endif //COLOR_HPP