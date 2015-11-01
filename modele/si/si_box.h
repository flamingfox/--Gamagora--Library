#ifndef SI_BOX_H
#define SI_BOX_H

#include "si_primitive.h"
#include "lib/box.h"

class SI_Box : public SI_Primitive, public Box
{
public:
    SI_Box(float cote, float e = 1.f, float R = 1.f);
    SI_Box(const vec3& min, const vec3& max, float e = 1.f, float R = 1.f);

    float potentiel(const glm::vec3& p) const;
    //virtual bool intersect(const Rayon& r, float &distance) const = 0;
    float distance(const glm::vec3& p) const;

protected:
    Box englob;
};

#endif // SI_BOX_H
