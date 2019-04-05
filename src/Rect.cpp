#include "Rect.h"
#include "Vec2.h"
#include <cstdio>
Rect :: Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){};

bool Rect :: Contains(const Vec2& point) {
    
    
    bool insideWidth = (point.x >= this->x ) && (point.x <= this->x+this->w);
    bool insideHeight = (point.y >= this->y) && (point.y <= this->y+this->h);
    return insideHeight && insideWidth;
}
bool Rect :: Contains(const int&x , const int& y) {
    Vec2 point(x,y);
    return this->Contains(point);
}
