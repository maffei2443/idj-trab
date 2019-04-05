#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
public:
    float x, y, w, h;
    Rect(float x = 0, float y = 0, float w = 0, float h = 0);
    bool Contains(const Vec2&);
    bool Contains(const int&, const int&);
};

#endif