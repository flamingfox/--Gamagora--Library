#include "si_box.h"

SI_Box::SI_Box(float cote, float e, float R):
        SI_Box(glm::vec3(-cote/2,-cote/2,-cote/2),glm::vec3(cote/2,cote/2,cote/2), e, R)
{
}

SI_Box::SI_Box(const vec3& min, const vec3& max, float e, float R):
        SI_Primitive(e,R), Box(min,max),    englob(Box(min-R,max+R))
{
}

float SI_Box::potentiel(const glm::vec3& p) const
{
    vec3 cote = (max-min)/2.f;

    vec3 pos = glm::abs(p - (min+cote));
    float val = 0.0;

    if(pos.x > cote.x)
        val += (cote.x - pos.x)*(cote.x - pos.x);

    if(pos.y > cote.y)
        val += (cote.y - pos.y)*(cote.y - pos.y);

    if(pos.z > cote.z)
        val += (cote.z - pos.z)*(cote.z - pos.z);

    return e*falloff(val,R);
}

float SI_Box::distance(const glm::vec3& p) const
{
    return englob.distance(p);
}
