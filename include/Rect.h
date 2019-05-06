#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect{
private:
    void UpdateCenter();
    double _x, _y, _w, _h;
public:
    double x, y, w, h;
    Vec2 center;
    Rect(double x = 0, double y = 0, double w = 0, double h = 0);
    void SetX(double);
    void SetY(double);
    void SetW(double);
    void SetH(double);
    void SetXY(double, double);
    void SetXWH (double x, double w = -1, double h = -1);
    void SetYWH (double y, double w = -1, double h = -1);
    void SetXYWH (double x, double y, double w = -1, double h = -1);
    bool Contains(const Vec2&);
    bool Contains(const int&, const int&);
};

#endif