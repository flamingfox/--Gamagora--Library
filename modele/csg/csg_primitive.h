#ifndef CSG_PRIMITIVE_H
#define CSG_PRIMITIVE_H
#include "../node.h"
#include "math.h"

///
/// \author Rudi Welter
/// \brief The CSG_Primitive class
///
class CSG_Primitive : public Node
{
public:
    CSG_Primitive();
    ~CSG_Primitive();
    virtual bool inOut(const Vector3D& p) const = 0;
    float potentiel(const Vector3D& p) const;
    //virtual bool intersect(const Rayon& r, float &distance) const = 0;
    virtual float distance(const Vector3D& p) const =0;


    Vector3D getNormal(const Vector3D& p, float eps) const;
    virtual Vector3D getNormal(const Vector3D& p) const = 0;
};

#endif // CSG_PRIMITIVE_H
