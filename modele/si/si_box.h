#ifndef SI_BOX_H
#define SI_BOX_H

#include "si_primitive.h"
#include "geometrie/box.h"

class SI_Box : public SI_Primitive, public Box
{
public:
    SI_Box(float cote, float e = 1.f, float R = 1.f);
    SI_Box(const Vector3D& min, const Vector3D& max, float e = 1.f, float R = 1.f);

    float potentiel(const Vector3D& p) const;
    //virtual bool intersect(const Rayon& r, float &distance) const = 0;
    float distance(const Vector3D& p) const;

protected:
    Box englob;
};

#endif // SI_BOX_H
