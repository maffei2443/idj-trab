#include "Rect.h"
#include "Vec2.h"
#include <cstdio>
#include <iostream>
using std::cout;
using std::endl;

void Rect::UpdateCenter() {
    this->center.x = (this->x+this->w)/2;
    this->center.y = (this->y+this->h)/2;
}



Rect::Rect(double x, double y, double w, double h) : _x(x), _y(y), _w(w), _h(h){
    this->UpdateCenter();
}

Rect::Rect(const Vec2& vec) {
    this->x = vec.x;    this->y = vec.y;
    this->w = 0;    this->h = 0;
    this->UpdateCenter();
}

void Rect::SetXYWH(double x, double y, double w, double h) {
    this->x = x;
    this->y = y;
    this->w = w > 0.0 ? w : this->w;
    this->h = h > 0.0 ? h : this->h;
    this->UpdateCenter();
}
void Rect::SetXWH (double x, double w, double h){
    this->SetXYWH(x, this->y, w, h);
}

void Rect::SetYWH (double y, double w, double h){
    this->SetXYWH(this->x, y, w, h);
}
void Rect::SetX(double x) {
    this->x = x;
    this->UpdateCenter();
}
void Rect::SetY(double y) {
    this->y = y;
    this->UpdateCenter();
}
void Rect::SetW(double w) {
    this->w = w;
    this->UpdateCenter();
}
void Rect::SetH(double h) {
    this->h = h;
    this->UpdateCenter();
}
void Rect::SetWH(double w, double h) {
    this->w = w;
    this->h = h;
    this->UpdateCenter();
}
void Rect::SetXY(double x, double y) {
    this->x = x; this->y = y;
    this->UpdateCenter();
}
void Rect::SetXY(const Vec2& vec) {
    this->SetXY(vec.x, vec.y);
}


bool Rect::Contains(const Vec2& point) {
    // //////printf("x,y ==> %f, %f\n", this->x, this->y);
    // //////printf("Point : x,y,w,h ==> %f, %f, %f, %f\n", point.x, point.y, this->w, this->h);
    bool insideWidth = (point.x >= this->x ) && (point.x <= this->x+this->w);
    bool insideHeight = (point.y >= this->y) && (point.y <= this->y+this->h);
    return insideHeight && insideWidth;
}
bool Rect::Contains(const int&x , const int& y) {
    Vec2 point(x,y);
    return this->Contains(point);
}

void Rect::AddXY(double _x, double _y) {
    this->SetXY(this->x+_x, this->y+_y);
}

void Rect::AddX(double _x) {
    this->SetX(this->x+_x);
}

void Rect::AddY(double _y) {
    this->SetY(this->y+_y);
}


void Rect::AddW(double _w) {
    this->SetW(this->w+_w);
}

void Rect::AddH(double _h) {
    this->SetH(this->h+_h);
}
void Rect::AddWH(double _w, double _h) {
    this->SetWH(this->w+_w, this->h+_h);
}

void Rect::Add(double x, double y, double w, double h) {
    this->x += x; this->y += y; this->w += w; this->h +=h;
    this->UpdateCenter();
}

void Rect::AddXYWH(double x, double y, double w, double h) {
    this->Add(x,y,w,h);
}

void Rect::Add(double add) {
    this->x += add; this->y += add; this->w += add; this->h +=add;
    this->UpdateCenter();
}


std::ostream & operator << (std::ostream &out, const Rect &ret) {
    out << "(x, y) == (" << ret.x << ", " << ret.y << ")\n";
    out << "Center: " << ret.center;
    out << "(x,y) == (" << ret.x << ", " << ret.y << ")\n";
    return out;
}


Rect Rect::operator+(const Rect& toAdd) const{
    return *this + toAdd;
}
Vec2 Rect::operator+(const Vec2& toAdd) const{
    return Vec2( this->x+toAdd.x, this->y+toAdd.y );
}

Rect Rect::operator-(const Rect& toSub) const{
    return {this->x - toSub.x, this->y - toSub.y,
            this->w-toSub.w, this->h-toSub.h};
}
Vec2 Rect::operator-(const Vec2& toSub) const{
    return Vec2( this->x-toSub.x, this->y-toSub.y );
}
Rect Rect::operator*(const Rect& toMul) const{
    return {this->x * toMul.x, this->y * toMul.y};
}
Rect Rect::operator/(const Rect& toSub) const{
    return {this->x / toSub.x, this->y / toSub.y};
}

void Rect::operator+=(const Rect& toAdd){
    this->x += toAdd.x;
    this->y += toAdd.y;
}
void Rect::operator-=(const Rect& toAdd){
    this->x -= toAdd.x;
    this->y -= toAdd.y;
}
void Rect::operator*=(const Rect& toAdd){
    this->x *= toAdd.x;
    this->y *= toAdd.y;
}
void Rect::operator/=(const Rect& toAdd){
    this->x /= toAdd.x;
    this->y /= toAdd.y;
}

// 

// Operação <vetor> & escalar
Rect Rect::operator+(const int& scalar) const{
    Rect neo(*this);
    neo.Add(scalar);
    return neo;
}
Rect Rect::operator-(const int& scalar) const{
    return {this->x  - scalar, this->y  - scalar};
}
Rect Rect::operator*(const int& scalar) const{
    return {this->x  * scalar, this->y  * scalar};
}
Rect Rect::operator/(const int& scalar) const{
    return {this->x  / scalar, this->y  / scalar};
}

void Rect::operator+=(const int& scalar){
    this->x += scalar;
    this->y += scalar;
}
void Rect::operator-=(const int& scalar){
    this->x -= scalar;
    this->y -= scalar;
}
void Rect::operator*=(const int& scalar){
    this->x *= scalar;
    this->y *= scalar;
}
void Rect::operator/=(const int& scalar){
    this->x /= scalar;
    this->y /= scalar;
}
Rect::operator Vec2() {
    return Vec2(this->x, this->y);
}