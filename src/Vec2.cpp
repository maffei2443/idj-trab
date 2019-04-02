#include "Vec2.h"
#include <cmath>

static float lineSlope(const Vec2& va, const Vec2& vb) {
    return ( (va.x - vb.x)/(va.y - vb.y) );
}

Vec2 :: Vec2() : x(0), y(0){}
Vec2 :: Vec2(float x, float y) : x(x), y(y){}
Vec2 :: Vec2(float x, float y) : x(x), y(y){}


Vec2 Vec2 :: operator+(const Vec2& toAdd) const{
    return {this->x+toAdd.x, this->y+toAdd.y};
}

Vec2 Vec2 :: operator-(const Vec2& toAdd) const{
    return {this->x-toAdd.x, this->y-toAdd.y};
}

Vec2 Vec2 :: operator*(const int& scalar) const{
    return {this->x  * scalar, this->y  * scalar};
}
Vec2 Vec2 :: operator/(const int& scalar) const{
    return {this->x  / scalar, this->y  / scalar};
}

float Vec2 :: abs() {
    return sqrt(this->x*this->x + this->y*this->y);
}

Vec2 Vec2 :: unitary() {
    return Vec2(this->x/abs(), this->y/abs());
}

float Vec2 :: dist(const Vec2& point) const {
    return sqrt( this->x*point.x + this->y*point.y );
}

float Vec2 :: xAxisSlope() const{
    return atan2(this->y, this->x);
}

void Vec2 :: rotate(const float& degree) {
    const float radian = degree * DEG2RAD;
    auto xOld = this->x;
    auto yOld = this->y;
    this->x = xOld * cos(radian) - yOld * sin(radian);
    this->y = yOld * cos(radian) + xOld * sin(radian);
}
