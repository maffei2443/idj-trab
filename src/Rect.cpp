#include "Rect.h"
#include "Vec2.h"
Rect :: Rect(float x=0, float y=0, float w=0, float h=0) : x(x), y(y), w(w), h(h){};

bool Rect :: Contains(const Vec2& point) {
    bool insideWidth = (this->x >= point.x) && (point.x <= this->x+this->w);
    bool insideHeight = (this->y >= point.y) && (point.y <= this->y+this->h);
    return insideHeight & insideWidth;
}
bool Rect :: Contains(const int&x , const int& y) {
    Vec2 point(x,y);
    return this->Contains(point);
}
