#ifndef SI_SPHERE_H
#define SI_SPHERE_H

#include "si_primitive.h"
#include "geometrie/sphere.h"

class SI_Sphere : public SI_Primitive, public Sphere
{
public:
    SI_Sphere(float rayonMin, float e = 1.f, float R = 1.f);
    SI_Sphere(const Vector3D& centre, float rayonMin, float e = 1.f, float R = 1.f);
    ~SI_Sphere();

    float potentiel(const Vector3D& p) const;
    //virtual bool intersect(const Rayon& r, float &distance) const = 0;
    float distance(const Vector3D& p) const;

protected:
    /**sphere englobante maximum dont l'énergie est toujours à 0.f en dehors*/
    Sphere englob;
};

#endif // SI_SPHERE_H
