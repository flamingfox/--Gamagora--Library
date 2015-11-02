#ifndef QUADRANGLE_H
#define QUADRANGLE_H

#include "geometrie/vector2d.h"

#include <iostream>
#include <math.h>

class Quadrangle
{
    /*
     *     p2      p3
     *      X-----X
     *      |     |
     *      |     |
     *      X-----X
     *    p1       p4
     */
    Vector2D p1, p2, p3, p4;

public:
    Quadrangle() : p1(0,0), p2(0,0), p3(0,0), p4(0,0){}
    Quadrangle(const Vector2D& _p1, const Vector2D& _p2, const Vector2D& _p3, const Vector2D& _p4)
        : p1(_p1), p2(_p2), p3(_p3), p4(_p4){}

    Vector2D& operator[] (int i) {
      if (i == 0)       return p1;
      else if(i == 1)   return p2;
      else if(i == 2)   return p3;
      else              return p4;
    }

    Vector2D operator[] (int i) const {
        if (i == 0)       return p1;
        else if(i == 1)   return p2;
        else if(i == 2)   return p3;
        else              return p4;
    }


    float area() const;
    float perimetre() const;

    void shrink(const float& l);
};

#endif // QUADRANGLE_H
