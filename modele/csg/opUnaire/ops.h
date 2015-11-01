#ifndef OPS_H
#define OPS_H

#include "opunaire.h"
#include "csg/csg_primitive.h"


class OpS: public OpUnaire
{
public:
    OpS(Node* a, const glm::vec3& scale);

    //bool intersect(const Rayon &r, float &distanceMin) const;
    vec3 getNormal(const vec3 &p, float eps) const;

    float distance(const glm::vec3 &p) const;

private:
    glm::vec3 scale;

protected:
    glm::vec3 deplace(const glm::vec3& p) const;
};


#endif // OPS_H
