#ifndef VEC2_H
#define VEC2_H

#define RAD2DEG (180 / M_PI)
#define DEG2RAD (M_PI / 180)
class Vec2 {
private:
    float norm;
public:
    static float lineSlope(const Vec2&, const Vec2&);
    float x, y;
    Vec2();
    Vec2(float, float);
    Vec2(const Vec2&);
    Vec2 operator+(const Vec2&) const;
    Vec2 operator-(const Vec2&) const;
    Vec2 operator*(const int&) const;
    Vec2 operator/(const int&) const;
    float abs();
    Vec2 unitary();
    float dist(const Vec2&) const;
    float xAxisSlope() const;
    void rotate(const float& degree);
    void GetRotated(const float& degree);
    // add rect and vet2
    // distancia dentro de rects
    // 4 operações elementares
};

#endif