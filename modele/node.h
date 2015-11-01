#ifndef NODE_H
#define NODE_H
#include "rendu/rayon.h"
#include "geometrie/vector3d.h"


/** @brief délimite la distance des hauteurs à calculer autour d'un point pour déterminer sa normale*/
#define RAYON_NORMAL 0.1f

///
/// \author Rudi Welter
/// \brief The Node class
///
class Node
{
public:
    Node();
    ~Node();
    virtual bool inOut(const Vector3D& p) const = 0;
    virtual float potentiel(const Vector3D& p) const = 0;
    virtual float distance(const Vector3D& p) const =0;

    //virtual bool intersect(const Rayon& r, float &distance) const =0;

    virtual Vector3D getNormal(const Vector3D& p, float eps = RAYON_NORMAL) const = 0;
};

#endif // NODE_H
