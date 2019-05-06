#include "Rect.h"
#include "Vec2.h"
#include <cstdio>
void Rect::UpdateCenter() {
    this->center.x = (this->x+this->w)/2;
    this->center.y = (this->y+this->h)/2;
}

Rect::Rect(double x, double y, double w, double h) : _x(x), _y(y), _w(w), _h(h){
    this->UpdateCenter();
};

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
void Rect::SetXY(double x, double y) {
    this->x = x; this->y = y;
    this->UpdateCenter();
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
