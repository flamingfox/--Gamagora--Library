#ifndef OPUNION_H
#define OPUNION_H

#include "opbin.h"

class OpUnion : public OpBin
{
public:
    OpUnion(Node* a, Node* b );

    bool inOut(const Vector3D &p) const;
    float potentiel(const Vector3D& p) const;
    float distance(const Vector3D &p) const;
    //bool intersect(const Rayon &r, float &t);

    Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const;

};

#endif // OPUNION_H
