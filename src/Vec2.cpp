#include "Vec2.h"
#include <cmath>
#define PI M_PI
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
// static double lineSlope(const Vec2& va, const Vec2& vb) {
//     return ( (va.x - vb.x)/(va.y - vb.y) );
// }

Vec2::Vec2() : x(0), y(0){}
Vec2::Vec2(double x, double y) : x(x), y(y){}
Vec2::Vec2(const Vec2& vet):x(vet.x), y(vet.y){}
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

void Vec2::operator+=(const Vec2& toAdd){
    this->x += toAdd.x;
    this->y += toAdd.y;
}
void Vec2::operator-=(const Vec2& toAdd){
    this->x -= toAdd.x;
    this->y -= toAdd.y;
}
void Vec2::operator*=(const Vec2& toAdd){
    this->x *= toAdd.x;
    this->y *= toAdd.y;
}
void Vec2::operator/=(const Vec2& toAdd){
    this->x /= toAdd.x;
    this->y /= toAdd.y;
}

// 

// Operação <vetor> & escalar
Vec2 Vec2::operator+(const int& scalar) const{
    return {this->x  + scalar, this->y  + scalar};
}
Vec2 Vec2::operator-(const int& scalar) const{
    return {this->x  - scalar, this->y  - scalar};
}
Vec2 Vec2::operator*(const int& scalar) const{
    return {this->x  * scalar, this->y  * scalar};
}
Vec2 Vec2::operator/(const int& scalar) const{
    return {this->x  / scalar, this->y  / scalar};
}

void Vec2::operator+=(const int& scalar){
    this->x += scalar;
    this->y += scalar;
}
void Vec2::operator-=(const int& scalar){
    this->x -= scalar;
    this->y -= scalar;
}
void Vec2::operator*=(const int& scalar){
    this->x *= scalar;
    this->y *= scalar;
}
void Vec2::operator/=(const int& scalar){
    this->x /= scalar;
    this->y /= scalar;
}

bool Vec2::operator==(const Vec2& vec) {
    return this->x == vec.x and this->y == vec.y;
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

void Vec2::rotate(double degree,  double offX,  double offY) {
    const double radian = degree * DEG2RAD;
    auto xOld = this->x-offX;
    auto yOld = this->y-offY;
    double coss = cos(radian);
    double sen = sin(radian);
    this->x = xOld * coss - yOld * sen + offX;
    this->y = yOld * coss + xOld * sen + offY;
}

Vec2 Vec2::GetRotated(const double& degree) {
    Vec2 toRotate(this->x, this->y);
    toRotate.rotate(degree);
    return toRotate;
}
std::ostream & operator << (std::ostream &out, const Vec2 &vec) {
    out << "(x,y) == (" << vec.x << ", " << vec.y << ")\n";
    return out;
}