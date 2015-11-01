#ifndef CSG_BOX_H
#define CSG_BOX_H

#include "lib/box.h"
#include "csg_primitive.h"


class CSG_Box : public CSG_Primitive,  public Box
{
public:
    CSG_Box(float cote);
    CSG_Box(const vec3& _min, const vec3& _max);
    bool inOut(const vec3& point) const;
    bool intersect(const Rayon &r, float &distanceMin) const;
    float distance(const glm::vec3& p) const;

    vec3 getNormal(const vec3& p) const;

private:
};

#endif // CSG_BOX_H
