#ifndef OPT_H
#define OPT_H

#include "opunaire.h"
#include "csg/csg_primitive.h"


class OpT: public OpUnaire
{
public:
    OpT(Node* a, const glm::vec3& tranlate);

    //bool intersect(const Rayon &r, float &distanceMin) const;
    vec3 getNormal(const vec3 &p, float eps) const;

private:
    glm::vec3 trans;

protected:
    glm::vec3 deplace(const glm::vec3& p) const;
};


#endif // OPT_H
