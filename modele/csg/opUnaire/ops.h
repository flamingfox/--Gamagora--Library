#ifndef OPS_H
#define OPS_H

#include "opunaire.h"
#include "../csg_primitive.h"


class OpS: public OpUnaire
{
public:
    OpS(Node* a, const Vector3D& scale);

    //bool intersect(const Rayon &r, float &distanceMin) const;
    Vector3D getNormal(const Vector3D &p, float eps) const;

    float distance(const Vector3D &p) const;

private:
    Vector3D scale;

protected:
    Vector3D deplace(const Vector3D& p) const;
};


#endif // OPS_H
