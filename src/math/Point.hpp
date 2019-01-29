#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

namespace Math {
    class Point {
    public:
        Point();
        Point(float x, float y, float z);
        Point(const Point &p);

        float dot(const Point &other);

        float &operator[](int);
        const float &operator[](int) const;

        friend std::ostream &operator<<(std::ostream &s, const Point &p);

        Point operator+(const Point &other) const;
        Point &operator+=(const Point &rhs);
        Point operator-(const Point &other) const;
        Point &operator-=(const Point &rhs);
        Point operator-() const;
        Point operator*(const float &mul) const;
        Point &operator*=(const float &mul);
        Point operator/(const float &mul) const;
        Point &operator/=(const float &mul);

        float x() const;
        float y() const;
        float z() const;

        void x(float val);
        void y(float val);
        void z(float val);

    private:
        float values[3];
    };
}

#endif // POINT_HPP
