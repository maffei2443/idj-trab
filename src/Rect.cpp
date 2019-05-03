#include "Rect.h"
#include "Vec2.h"
#include <cstdio>
Rect::Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h){
    this->center.x = (x+w)/2;
    this->center.y = (y+h)/2;
};

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
