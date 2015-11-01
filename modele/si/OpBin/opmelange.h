#ifndef OPMELANGE_H
#define OPMELANGE_H

#include "si_primitive.h"
#include <vector>

class opMelange : public Node
{
public:
    opMelange();
    opMelange(Node* prim);
    opMelange(Node* a, Node* b);
    opMelange(std::vector<Node*> prims);

    opMelange* addPrim(Node* prim);
    bool inOut(const vec3 &p) const;

    float potentiel(const glm::vec3& p) const;
    float distance(const glm::vec3& p) const;

    vec3 getNormal(const vec3& p, float eps = RAYON_NORMAL) const;

protected:
    std::vector<Node*> primitives;
};

#endif // OPMELANGE_H
