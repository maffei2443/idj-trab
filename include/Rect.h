#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
public:
    float x, y, w, h;
    Rect();
    Rect(float, float, float, float);
    bool Contains(const Vec2&);
    bool Contains(const int&, const int&);
};

#endif