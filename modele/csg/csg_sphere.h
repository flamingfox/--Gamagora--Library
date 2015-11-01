#ifndef CSG_SPHERE_H
#define CSG_SPHERE_H

#include "geometrie/sphere.h"
#include "csg_primitive.h"

class CSG_Sphere : public CSG_Primitive,  public Sphere
{
public:
    CSG_Sphere(float r);
    CSG_Sphere(const Vector3D &c, float r);

    bool inOut(const Vector3D& p) const;
    bool intersect(const Rayon &r, float &distanceMin) const;
    float distance(const Vector3D& p) const;

    Vector3D getNormal(const Vector3D& p) const;
};

#endif // CSG_SPHERE_H
