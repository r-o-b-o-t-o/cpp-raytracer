#ifndef COLOR_HPP
#define COLOR_HPP

namespace Scene {
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

    protected:
        float _r;
        float _g;
        float _b;
    };
}

#endif //COLOR_HPP