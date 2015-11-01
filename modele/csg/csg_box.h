#ifndef CSG_BOX_H
#define CSG_BOX_H

#include "geometrie/box.h"
#include "csg_primitive.h"


class CSG_Box : public CSG_Primitive,  public Box
{
public:
    CSG_Box(float cote);
    CSG_Box(const Vector3D& _min, const Vector3D& _max);
    bool inOut(const Vector3D& point) const;
    bool intersect(const Rayon &r, float &distanceMin) const;
    float distance(const Vector3D& p) const;

    Vector3D getNormal(const Vector3D& p) const;

private:
};

#endif // CSG_BOX_H
