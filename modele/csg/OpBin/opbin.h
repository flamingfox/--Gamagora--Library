#ifndef OPBIN_H
#define OPBIN_H

#include "node.h"
#include <algorithm>    // std::max

class OpBin : public Node
{
public:
    OpBin(Node* _a, Node* _b);    //info technique: selon le debbugeur, le _a perd sa caractéristique de Sphère (pointeur "Sphere::vprt" inaccessible) quand le _b prend ça valeur. C'est pour ça que j'ai passé en pointeur et pas en adresse.
    ~OpBin();

    virtual bool inOut(const glm::vec3& p) const = 0;
    virtual float potentiel(const glm::vec3& p) const = 0;
    //virtual bool intersect(const Rayon& r, float &distance) const =0;
    float distance(const glm::vec3& p) const;

    virtual vec3 getNormal(const vec3& p, float eps = RAYON_NORMAL) const = 0;

protected:
    Node *a, *b;
};

#endif // OPBIN_H
