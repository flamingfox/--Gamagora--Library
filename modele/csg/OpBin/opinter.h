#ifndef OPINTER_H
#define OPINTER_H

#include "opbin.h"

class OpInter : public OpBin
{
public:
    OpInter(Node* a, Node* b );

    bool inOut(const Vector3D &p) const;
    float potentiel(const Vector3D& p) const;
    float distance(const Vector3D &p) const;
    //bool intersect(const Rayon &r, float &t);

    Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const;

};

#endif // OPINTER_H
