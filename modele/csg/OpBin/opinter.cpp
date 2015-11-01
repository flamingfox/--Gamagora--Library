#include "opinter.h"

OpInter::OpInter(Node *a, Node *b) :
    OpBin(a, b)
{

}

bool OpInter::inOut(const glm::vec3& p) const
{
    return (a->inOut(p) && b->inOut(p));
}

float OpInter::potentiel(const glm::vec3& p) const
{
    return std::min(a->potentiel(p), b->potentiel(p));

}

float OpInter::distance(const glm::vec3 &p) const
{
    return std::min(a->distance(p), b->distance(p));
}

/*bool OpInter::intersect(const Rayon& r, float& t)
{
    float tTmp = 0;

    if(a.intersect(r, tTmp) && b.intersect(r, t)){

        if(tTmp < t)
            t = tTmp;

        retour = true;

    }
    return false;
}*/

glm::vec3 OpInter::getNormal(const vec3& p, float eps) const
{
    return a->getNormal(p,eps);
    //à revoir
}

