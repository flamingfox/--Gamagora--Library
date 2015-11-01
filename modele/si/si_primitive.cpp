#include "si_primitive.h"

SI_Primitive::SI_Primitive()
{
}


SI_Primitive::SI_Primitive(float e, float R):
    e(e), R(R)
{
}

bool SI_Primitive::inOut(const Vector3D &p) const
{
    return potentiel(p) >= 0.5f;
}


// Smooth falloff function
// r : small radius
// R : Large radius
float SI_Primitive::falloff( float r, float R ) const //fonction G du cours
{
    //glm::clamp(x, minVal, maxVal) = min(max(x, minVal), maxVal)
    //float x = glm::clamp(r/R,0.f,1.f);

    float x = std::min( std::max(r/R, 0.f), 1.f ) ;
    float y = (1.f-x*x);
    return y*y*y;
}

Vector3D SI_Primitive::getNormal(const Vector3D& p, float eps) const
{
    float v = potentiel(p);
    Vector3D n(  potentiel( Vector3D(p.x+eps, p.y, p.z) ) - v,
                 potentiel( Vector3D(p.x, p.y+eps, p.z) ) - v,
                 potentiel( Vector3D(p.x, p.y, p.z+eps) ) - v);
    /*n += Vector3D(potentiel( Vector3D(p.x-eps, p.y, p.z) ) - v,
            potentiel( Vector3D(p.x, p.y-eps, p.z) ) - v,
            potentiel( Vector3D(p.x, p.y, p.z-eps) ) - v);*/
    return - n.normalized();
}
