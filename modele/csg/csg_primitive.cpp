#include "csg_primitive.h"

CSG_Primitive::CSG_Primitive()
{

}

CSG_Primitive::~CSG_Primitive(){

}

float CSG_Primitive::potentiel(const glm::vec3& p) const
{
    return inOut(p) ?   1.f :   0.f;
}


vec3 CSG_Primitive::getNormal(const vec3& p, float eps) const
{
    return getNormal(p);
    (void) eps;
}
