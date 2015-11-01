#include "ops.h"


OpS::OpS(Node *a, const Vector3D& scale):
    OpUnaire(a),   scale(scale)
{
}

Vector3D OpS::deplace(const Vector3D& p) const
{
    return p/scale;
}

/*************************************************************************************/


/*bool OpS::intersect(const Rayon &r, float &distanceMin) const
{
    return a->intersect(Rayon(r.getOrigine()/scale, r.getDirection()/scale), distanceMin);
}*/


Vector3D OpS::getNormal(const Vector3D &p, float eps) const
{
    return (a->getNormal(deplace(p), eps)*scale).normalized();
}

float OpS::distance(const Vector3D &p) const
{
    return scale.squareLength() * a->distance(deplace(p));
    //a revoir; marche quand le redimensionnement x==y==z
}
