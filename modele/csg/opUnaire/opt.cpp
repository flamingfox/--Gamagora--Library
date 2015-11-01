#include "opt.h"

OpT::OpT(Node *a, const Vector3D& translate):
    OpUnaire(a),   trans(translate)
{
}

Vector3D OpT::deplace(const Vector3D& p) const
{
    return p-trans;
}

/*************************************************************************************/


/*bool OpT::intersect(const Rayon &r, float &distanceMin) const
{
    return a->intersect(Rayon(r.getOrigine()-trans, r.getDirection()), distanceMin);
}*/

Vector3D OpT::getNormal(const Vector3D &p, float eps) const
{
    return a->getNormal(deplace(p), eps);
}
