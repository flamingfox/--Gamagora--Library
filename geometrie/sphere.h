#ifndef SPHERE_H
#define SPHERE_H

#include "rendu/rayon.h"
#include "geometrie/vector3d.h"

class Sphere
{
public:
    Sphere();
    Sphere(const Vector3D& centre, float rayon);

    bool intersect(const Rayon& r, float& minDist, float& maxDist) const;
    bool inOut(const Vector3D& p) const;
    float distance(const Vector3D &p) const;

    Vector3D getNormal(const Vector3D& p) const;

    float getRayon() const;

    protected:

    Vector3D centre;
    float rayon;
};

#endif // SPHERE_H
