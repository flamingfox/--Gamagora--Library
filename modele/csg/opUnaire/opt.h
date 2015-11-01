#ifndef OPT_H
#define OPT_H

#include "opunaire.h"
#include "../csg_primitive.h"


class OpT: public OpUnaire
{
public:
    OpT(Node* a, const Vector3D& tranlate);

    //bool intersect(const Rayon &r, float &distanceMin) const;
    Vector3D getNormal(const Vector3D &p, float eps) const;

private:
    Vector3D trans;

protected:
    Vector3D deplace(const Vector3D& p) const;
};


#endif // OPT_H
