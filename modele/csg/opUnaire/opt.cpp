#include "opUnaire/opt.h"

OpT::OpT(Node *a, const glm::vec3& translate):
    OpUnaire(a),   trans(translate)
{
}

glm::vec3 OpT::deplace(const glm::vec3& p) const
{
    return p-trans;
}

/*************************************************************************************/


/*bool OpT::intersect(const Rayon &r, float &distanceMin) const
{
    return a->intersect(Rayon(r.getOrigine()-trans, r.getDirection()), distanceMin);
}*/

vec3 OpT::getNormal(const vec3 &p, float eps) const
{
    return a->getNormal(deplace(p), eps);
}
