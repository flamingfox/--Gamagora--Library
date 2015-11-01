#ifndef CSG_PRIMITIVE_H
#define CSG_PRIMITIVE_H
#include "node.h"
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
    virtual bool inOut(const glm::vec3& p) const = 0;
    float potentiel(const glm::vec3& p) const;
    //virtual bool intersect(const Rayon& r, float &distance) const = 0;
    virtual float distance(const glm::vec3& p) const =0;


    vec3 getNormal(const vec3& p, float eps) const;
    virtual vec3 getNormal(const vec3& p) const = 0;
};

#endif // CSG_PRIMITIVE_H
