#ifndef OPUNAIRE_H
#define OPUNAIRE_H

#include "node.h"
#include "csg/csg_primitive.h"


class OpUnaire : public Node
{
public:
    OpUnaire(Node* a);
    ~OpUnaire();

    bool inOut(const glm::vec3 &p) const;
    float potentiel(const glm::vec3& p) const;
    //virtual bool intersect(const Rayon &r, float &distanceMin) const = 0;
    virtual float distance(const glm::vec3& p) const;

    virtual vec3 getNormal(const vec3& p, float eps = RAYON_NORMAL) const = 0;

protected:
    Node* a;   //à remplacer par une Node* pour la suite

    virtual glm::vec3 deplace(const glm::vec3& p) const = 0;
};


#endif // OPUNAIRE_H
