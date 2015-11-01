#include "opunion.h"

OpUnion::OpUnion(Node* a, Node* b) :
    OpBin(a, b)
{
}


bool OpUnion::inOut(const Vector3D& p) const
{
    return (a->inOut(p) || b->inOut(p));
}

float OpUnion::potentiel(const Vector3D& p) const
{
    return std::max(a->potentiel(p), b->potentiel(p));
}

float OpUnion::distance(const Vector3D &p) const
{
    return std::min(a->distance(p), b->distance(p));
}

/*bool OpUnion::intersect(const Rayon& r, float& t)
{
    bool ba = a->intersect(r, t);

    float tTmp;
    if(b->intersect(r, tTmp))
    {
        if(ba == false || tTmp < t)
            t = tTmp;
        return true;
    }
    else
        return ba;
}*/

Vector3D OpUnion::getNormal(const Vector3D& p, float eps) const
{
    if(a->distance(p) <= b->distance(p))
        return a->getNormal(p, eps);
    else
        return b->getNormal(p, eps);
}

