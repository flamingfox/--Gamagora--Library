#include "csg_primitive.h"

CSG_Primitive::CSG_Primitive()
{

}

CSG_Primitive::~CSG_Primitive(){

}

float CSG_Primitive::potentiel(const Vector3D& p) const
{
    return inOut(p) ?   1.f :   0.f;
}


Vector3D CSG_Primitive::getNormal(const Vector3D& p, float eps) const
{
    return getNormal(p);
    (void) eps;
}
