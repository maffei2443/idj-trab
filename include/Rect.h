#ifndef RECT_H
#define RECT_H

#include "Vec2.h"
#include <iostream>
using std::cout;
using std::endl;

class Rect{
private:
    void UpdateCenter();
    void _Mul(double);
public:
    double x, y, w, h;
    Vec2 center;
    Rect(double x = 0, double y = 0, double w = 0, double h = 0);
    Rect(const Vec2& vec);
    void SetCenter(Vec2);
    void SetCenter(Rect);
    void SetCenter(double, double);
    void SetX(double);
    void SetY(double);
    void SetW(double);
    void SetH(double);
    void SetWH(double, double);
    void SetXY(double, double);
    void SetXY(const Vec2&);
    void SetXWH (double x, double w = -1, double h = -1);
    void SetYWH (double y, double w = -1, double h = -1);
    void SetXYWH (double x, double y, double w = -1, double h = -1);
    void AddX(double _x=0);  // incrementa x  e atualiza o centro
    void AddY(double _y=0);  // incrementa y e atualiza o centro
    void AddXY(double _x=0, double _y=0);  // incrementa x e y e atualiza o centro
    void AddW(double _w=0);  // incrementa w  e atualiza o centro
    void AddH(double _h=0);  // incrementa h e atualiza o centro
    void AddWH(double _w=0, double _h=0);  // incrementa w e h e atualiza o centro
    void Add(double, double, double, double);
    void AddXYWH(double, double, double, double);
    void Add(double);
    bool Contains(const Vec2&);
    bool Contains(const int&, const int&);

    Rect operator+(const Rect&) const;
    Vec2 operator+(const Vec2& toAdd) const;
    Rect operator-(const Rect&) const;
    Vec2 operator-(const Vec2& toAdd) const;
    Rect operator*(const Rect&) const;
    Rect operator/(const Rect&) const;

    void operator+=(const Rect&);
    void operator-=(const Rect&);
    void operator*=(const Rect&);
    void operator/=(const Rect&);

    Rect operator+(const int&) const;
    Rect operator-(const int&) const;
    Rect operator*(const int&) const;
    Rect operator/(const int&) const;

    void operator+=(const int&);
    void operator-=(const int&);
    void operator*=(const int&);
    void operator/=(const int&);

    operator Vec2();
    Vec2 castVec2();

};
std::ostream & operator << (std::ostream &, const Rect &);
#endif