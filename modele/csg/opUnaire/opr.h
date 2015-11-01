#ifndef OPR_H
#define OPR_H

#include "opunaire.h"
#include "csg/csg_primitive.h"
#include <math.h>

class OpR: public OpUnaire
{
public:
    OpR(Node* a, const glm::vec3& axe, float angle);

    //bool intersect(const Rayon &r, float &distanceMin) const;
    vec3 getNormal(const vec3 &p, float eps) const;

private:
    //glm::vec3 centre;     //a vec3(0,0,0) pour être plus logique avec les fonctions de rotation des logiciels de synthèse.
    glm::vec3 axe;  //direction de l'axe de rotation de centre "centre" autour duquel on tourne
    float angle;    //angle de rotation autour de l'axe "axe"

protected:
    glm::vec3 deplace(const glm::vec3& p) const;
    glm::vec3 rotate(const vec3& p, float angle) const;
};


#endif // OPR_H
