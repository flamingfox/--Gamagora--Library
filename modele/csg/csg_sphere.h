#ifndef CSG_SPHERE_H
#define CSG_SPHERE_H

#include "lib/sphere.h"
#include "csg_primitive.h"

class CSG_Sphere : public CSG_Primitive,  public Sphere
{
public:
    CSG_Sphere(float r);
    CSG_Sphere(const glm::vec3 &c, float r);

    bool inOut(const vec3& p) const;
    bool intersect(const Rayon &r, float &distanceMin) const;
    float distance(const vec3& p) const;

    vec3 getNormal(const vec3& p) const;
};

#endif // CSG_SPHERE_H
