#ifndef OPMELANGE_H
#define OPMELANGE_H

#include "float.h"  //FLT_MIN FLT_MAX

#include "../si_primitive.h"
#include <vector>

class opMelange : public Node
{
public:
    opMelange();
    opMelange(Node* prim);
    opMelange(Node* a, Node* b);
    opMelange(std::vector<Node*> prims);

    opMelange* addPrim(Node* prim);
    bool inOut(const Vector3D &p) const;

    float potentiel(const Vector3D& p) const;
    float distance(const Vector3D& p) const;

    Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const;

protected:
    std::vector<Node*> primitives;
};

#endif // OPMELANGE_H
