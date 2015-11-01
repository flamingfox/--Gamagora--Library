#include "opmelange.h"

opMelange::opMelange()
{
}

opMelange::opMelange(Node* prim)
{
    primitives.push_back(prim);
}
opMelange::opMelange(Node* a, Node* b)
{
    primitives.push_back(a);
    primitives.push_back(b);
}

opMelange::opMelange(std::vector<Node*> prims)
{
    primitives = prims;
}

/**********************************************************************/

opMelange* opMelange::addPrim(Node* prim)
{
    primitives.push_back(prim);
    return this;
}

/**********************************************************************/

bool opMelange::inOut(const vec3 &p) const
{
    return potentiel(p) >= 0.5f;
}


float opMelange::potentiel(const glm::vec3& p) const
{
    float f = 0.f;
    for(const Node* prim : primitives)
        f += prim->potentiel(p);

    return f;
}
float opMelange::distance(const glm::vec3& p) const
{
    float min = FLT_MAX;
    for(const Node* prim : primitives)  {
        float d = prim->distance(p);
        if(d < min)
            min = d;
    }
    return min;
}

glm::vec3 opMelange::getNormal(const vec3& p, float eps) const
{
  float v = potentiel(p);
  glm::vec3 n(  potentiel( glm::vec3(p.x+eps, p.y, p.z) ) - v,
                potentiel( glm::vec3(p.x, p.y+eps, p.z) ) - v,
                potentiel( glm::vec3(p.x, p.y, p.z+eps) ) - v);
  /*n += vec3(potentiel( glm::vec3(p.x-eps, p.y, p.z) ) - v,
            potentiel( glm::vec3(p.x, p.y-eps, p.z) ) - v,
            potentiel( glm::vec3(p.x, p.y, p.z-eps) ) - v);*/
  return -normalize(n);
}
