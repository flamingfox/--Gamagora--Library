#ifndef OPUNION_H
#define OPUNION_H

#include "opbin.h"

class OpUnion : public OpBin
{
public:
    OpUnion(Node* a, Node* b );

    bool inOut(const glm::vec3 &p) const;
    float potentiel(const glm::vec3& p) const;
    float distance(const glm::vec3 &p) const;
    //bool intersect(const Rayon &r, float &t);

    vec3 getNormal(const vec3& p, float eps = RAYON_NORMAL) const;

};

#endif // OPUNION_H
