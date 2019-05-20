#include "Rect.h"
#include "Vec2.h"
#include <cstdio>
#include <iostream>
#include "Util.h"
using std::cout;
using std::endl;

void Rect::UpdateCenter() {
    this->center = Vec2( this->x+(this->w/2), this->y+(this->h/2) );
}

Rect::Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h){
    this->UpdateCenter();
}

Rect::Rect(const Vec2& vec) {
    this->x = vec.x;    this->y = vec.y;
    this->w = 0;    this->h = 0;
    this->UpdateCenter();
}

Vec2 Rect::GetCenter() {
    return Vec2(this->x+this->w/2, this->y+this->h/2);
}

void Rect::SetCenter(Vec2 newCenter) {
    this->SetXY( newCenter.x-this->w/2, newCenter.y-this->h/2 );
}

void Rect::SetCenter(double x, double y) {
    this->SetXY( x-this->w/2, y-this->h/2 );
}
void Rect::SetCenter(Rect rect) {
    this->SetXY( rect.GetCenter().x-this->w/2, rect.GetCenter().y-this->h/2 );
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
    this->w = w; this->h = h;
    this->UpdateCenter();
}
void Rect::SetXY(double x, double y) {
    this->x = x; this->y = y;
    this->UpdateCenter();
}
void Rect::SetXY(const Vec2& vec) {
    this->SetXY(vec.x, vec.y);
}


void Rect::SetXWH (double x, double w, double h){
    this->SetXYWH(x, this->y, w, h);
}

void Rect::SetYWH (double y, double w, double h){
    this->SetXYWH(this->x, y, w, h);
}

void Rect::SetXYWH(double x, double y, double w, double h) {
    this->x = x;
    this->y = y;
    // QUE BUG BESTA...... SE MATA NA MORAL
    this->w = IsDoubleZero(w) ? 0 : w;
    this->h = IsDoubleZero(h) ? 0 : h;
    this->UpdateCenter();
}

void Rect::AddX(double _x) {
    this->SetX(this->x+_x);
}

void Rect::AddY(double _y) {
    this->SetY(this->y+_y);
}

void Rect::AddXY(double _x, double _y) {    
  this->SetXY(this->x+_x, this->y+_y);
}

void Rect::AddXY(Vec2 rect) {
    this->SetXY(this->x+rect.x, this->y+rect.y);
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

bool Rect::Contains(const Vec2& point) {
    // //////printf("x,y ==> %f, %f\n", this->x, this->y);
    // //////printf("Point : x,y,w,h ==> %f, %f, %f, %f\n", point.x, point.y, this->w, this->h);
    bool insideWidth = (point.x >= this->x ) and (point.x <= this->x+this->w);
    bool insideHeight = (point.y >= this->y) and (point.y <= this->y+this->h);
    return insideHeight and insideWidth;
}
bool Rect::Contains(const int&x , const int& y) {
    Vec2 point(x,y);
    return this->Contains(point);
}


std::ostream & operator << (std::ostream &out, const Rect &ret) {
    out << "(x, y, w, h) == (";
    out << ret.x << ", " << ret.y << ", " << ret.w << ", " << ret.h << ")";
    return out;
}


Rect Rect::operator+(const Rect& toAdd) const{
    return *this + toAdd;
}
Vec2 Rect::operator+(const Vec2& toAdd) const{
    return Vec2( this->x+toAdd.x, this->y+toAdd.y );
}

Rect Rect::operator-(const Rect& toSub) const{
    double deltaX = this->x-toSub.x;
    double deltaY = this->y-toSub.y;
    double deltaW = this->w-toSub.w;
    double deltaH = this->h-toSub.h;
    Rect t = Rect(
            /* IsDoubleZero(deltaX) ? 0.0: */ deltaX ,
            /* IsDoubleZero(deltaY) ? 0.0: */ deltaY ,
            /* IsDoubleZero(deltaW) ? 0.0: */ deltaW ,
            /* IsDoubleZero(deltaH) ? 0.0: */ deltaH );
    return t;
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
    // cout << "NUNCA MAIS VOU ME ENTREGAR\n"; abort();
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

Vec2 Rect::castVec2() {
    return Vec2(this->x, this->y);
}