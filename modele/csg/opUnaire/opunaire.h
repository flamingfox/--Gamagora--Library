#ifndef OPUNAIRE_H
#define OPUNAIRE_H

#include "../../node.h"
#include "../csg_primitive.h"


class OpUnaire : public Node
{
public:
    OpUnaire(Node* a);
    ~OpUnaire();

    bool inOut(const Vector3D &p) const;
    float potentiel(const Vector3D& p) const;
    //virtual bool intersect(const Rayon &r, float &distanceMin) const = 0;
    virtual float distance(const Vector3D& p) const;

    virtual Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const = 0;

protected:
    Node* a;   //à remplacer par une Node* pour la suite

    virtual Vector3D deplace(const Vector3D& p) const = 0;
};


#endif // OPUNAIRE_H
