#include "si_sphere.h"


SI_Sphere::SI_Sphere(float rayonMin, float e, float R):
        SI_Sphere(Vector3D(0,0,0), rayonMin, e, R)
{
}

SI_Sphere::SI_Sphere(const Vector3D& centre, float rayonMin, float e, float R):
        SI_Primitive(e, R), Sphere(centre, rayonMin),   englob(Sphere(centre, rayonMin+R))
{
}

SI_Sphere::~SI_Sphere()
{
}

float SI_Sphere::potentiel(const Vector3D &p) const
{
    float dist2 = p.Squaredistance(centre);


    if(dist2 >= englob.getRayon()*englob.getRayon())
        return 0.f;
    else if(dist2 <= rayon*rayon)
        return e;

    float r = sqrt(dist2)-rayon;//interp::interp_linear1D(sqrt(dist2), 0.f, R, rayon, englob.getRayon());
    return e*falloff(r,R);
}

float SI_Sphere::distance(const Vector3D &p) const
{
    return englob.distance(p);
}
