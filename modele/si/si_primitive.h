#ifndef SI_PRIMITIVE_H
#define SI_PRIMITIVE_H

#include "../node.h"
#include "math/interpolation.h"

#include <algorithm>

class SI_Primitive : public Node
{
public:
    SI_Primitive();
    SI_Primitive(float e, float R);

    bool inOut(const Vector3D& p) const;
    virtual float potentiel(const Vector3D& p) const = 0;
    //virtual bool intersect(const Rayon& r, float &distance) const = 0;
    virtual float distance(const Vector3D& p) const =0;

    Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const;

protected:
    float e;    //energie
    float R;    //rayon d'action du squelette au dela duquel la primitive n'a plus d'impact

    float falloff( float r, float R ) const;
};

#endif // SI_PRIMITIVE_H
