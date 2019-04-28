#ifndef VEC2_H
#define VEC2_H

#define RAD2DEG (180 / M_PI)
#define DEG2RAD (M_PI / 180)
class Vec2 {
private:
    double norm;
public:
    static double lineSlope(const Vec2&, const Vec2&);
    double x, y;
    Vec2();
    Vec2(double, double);
    Vec2(const Vec2&);
    Vec2 operator+(const Vec2&) const;
    Vec2 operator-(const Vec2&) const;
    Vec2 operator*(const Vec2&) const;
    Vec2 operator/(const Vec2&) const;

    Vec2 operator+(const int&) const;
    Vec2 operator-(const int&) const;
    Vec2 operator*(const int&) const;
    Vec2 operator/(const int&) const;


    double abs();
    Vec2 unitary();
    double dist(const Vec2&) const;
    double xAxisSlope() const;
    void rotate(const double& degree);
    Vec2 GetRotated(const double& degree);
    // add rect and vet2
    // distancia dentro de rects
    // 4 operações elementares
};

#endif