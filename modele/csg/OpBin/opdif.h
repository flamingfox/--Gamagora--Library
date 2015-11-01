#ifndef OPDIF_H
#define OPDIF_H

#include "opbin.h"


class OpDif: public OpBin
{
public:
    OpDif(Node* _a, Node* _b);


    bool inOut(const Vector3D &p) const;
    float potentiel(const Vector3D& p) const;
    float distance(const Vector3D &p) const;
    //bool intersect(const Rayon &r, float &t);

    Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const;

};

#endif // OPDIF_H
