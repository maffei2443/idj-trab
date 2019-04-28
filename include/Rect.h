#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
public:
    double x, y, w, h;
    Rect(double x = 0, double y = 0, double w = 0, double h = 0);
    bool Contains(const Vec2&);
    bool Contains(const int&, const int&);
};

#endif