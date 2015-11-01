#ifndef OPR_H
#define OPR_H

#include "opunaire.h"
#include "../csg_primitive.h"
#include <math.h>

class OpR: public OpUnaire
{
public:
    OpR(Node* a, const Vector3D& axe, float angle);

    //bool intersect(const Rayon &r, float &distanceMin) const;
    Vector3D getNormal(const Vector3D &p, float eps) const;

private:
    //Vector3D centre;     //a Vector3D(0,0,0) pour être plus logique avec les fonctions de rotation des logiciels de synthèse.
    Vector3D axe;  //direction de l'axe de rotation de centre "centre" autour duquel on tourne
    float angle;    //angle de rotation autour de l'axe "axe"

protected:
    Vector3D deplace(const Vector3D& p) const;
    Vector3D rotate(const Vector3D& p, float angle) const;
};


#endif // OPR_H
