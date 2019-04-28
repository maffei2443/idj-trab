#include "Vec2.h"
#include <cmath>
#define PI M_PI

// static double lineSlope(const Vec2& va, const Vec2& vb) {
//     return ( (va.x - vb.x)/(va.y - vb.y) );
// }

Vec2::Vec2() : x(0), y(0){}
Vec2::Vec2(double x, double y) : x(x), y(y){}

// Operações elementares entre vetores

Vec2 Vec2::operator+(const Vec2& toAdd) const{
    return {this->x+toAdd.x, this->y+toAdd.y};
}
Vec2 Vec2::operator-(const Vec2& toSub) const{
    return {this->x - toSub.x, this->y - toSub.y};
}
Vec2 Vec2::operator*(const Vec2& toMul) const{
    return {this->x * toMul.x, this->y * toMul.y};
}

Vec2 Vec2::operator/(const Vec2& toSub) const{
    return {this->x / toSub.x, this->y / toSub.y};
}
// 

// Operação <vetor> & escalar
Vec2 Vec2::operator*(const int& scalar) const{
    return {this->x  * scalar, this->y  * scalar};
}
Vec2 Vec2::operator/(const int& scalar) const{
    return {this->x  / scalar, this->y  / scalar};
}
Vec2 Vec2::operator+(const int& scalar) const{
    return {this->x  + scalar, this->y  + scalar};
}
Vec2 Vec2::operator-(const int& scalar) const{
    return {this->x  - scalar, this->y  - scalar};
}

double Vec2::abs() {
    return sqrt(this->x*this->x + this->y*this->y);
}

Vec2 Vec2::unitary() {
    this->norm = this->abs();
    return Vec2(this->x/this->norm, this->y/this->norm);
}

double Vec2::dist(const Vec2& point) const {
    double deltaX = this->x-point.x;
    double deltaY = this->x-point.y;
    return sqrt( deltaX*deltaX + deltaY*deltaY );
}

double Vec2::xAxisSlope() const{
    return atan2(this->y, this->x);
}

void Vec2::rotate(const double& degree) {
    const double radian = degree * DEG2RAD;
    auto xOld = this->x;
    auto yOld = this->y;
    this->x = xOld * cos(radian) - yOld * sin(radian);
    this->y = yOld * cos(radian) + xOld * sin(radian);
}

Vec2 Vec2::GetRotated(const double& degree) {
    Vec2 toRotate(this->x, this->y);
    toRotate.rotate(degree);
    return toRotate;
}
