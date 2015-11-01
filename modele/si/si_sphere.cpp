#include "si_sphere.h"


SI_Sphere::SI_Sphere(float rayonMin, float e, float R):
        SI_Sphere(vec3(0,0,0), rayonMin, e, R)
{
}

SI_Sphere::SI_Sphere(const vec3& centre, float rayonMin, float e, float R):
        SI_Primitive(e, R), Sphere(centre, rayonMin),   englob(Sphere(centre, rayonMin+R))
{
}

SI_Sphere::~SI_Sphere()
{
}

float SI_Sphere::potentiel(const vec3 &p) const
{
    float dist2 = distance2(p,centre);


    if(dist2 >= englob.getRayon()*englob.getRayon())
        return 0.f;
    else if(dist2 <= rayon*rayon)
        return e;

    float r = sqrt(dist2)-rayon;//interp::interp_linear1D(sqrt(dist2), 0.f, R, rayon, englob.getRayon());
    return e*falloff(r,R);
}

float SI_Sphere::distance(const vec3 &p) const
{
    return englob.distance(p);
}
