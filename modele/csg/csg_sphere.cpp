#include "csg_sphere.h"

CSG_Sphere::CSG_Sphere(float r):
    Sphere(Vector3D(0,0,0), r)
{
}

CSG_Sphere::CSG_Sphere(const Vector3D &c, float r):
    Sphere(c, r)
{
}


bool CSG_Sphere::inOut(const Vector3D& point) const
{
    return Sphere::inOut(point);
}



bool CSG_Sphere::intersect(const Rayon &r, float &distanceMin) const
{
    float distanceMax;
    return Sphere::intersect(r, distanceMin, distanceMax);
}

float CSG_Sphere::distance(const Vector3D &p) const
{
    Sphere::distance(p);
}

Vector3D CSG_Sphere::getNormal(const Vector3D &p) const
{
    return Sphere::getNormal(p);
}
