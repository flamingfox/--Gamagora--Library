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

bool opMelange::inOut(const Vector3D &p) const
{
    return potentiel(p) >= 0.5f;
}


float opMelange::potentiel(const Vector3D& p) const
{
    float f = 0.f;
    for(const Node* prim : primitives)
        f += prim->potentiel(p);

    return f;
}
float opMelange::distance(const Vector3D& p) const
{
    float min = FLT_MAX;
    for(const Node* prim : primitives)  {
        float d = prim->distance(p);
        if(d < min)
            min = d;
    }
    return min;
}

Vector3D opMelange::getNormal(const Vector3D& p, float eps) const
{
  float v = potentiel(p);
  Vector3D n(  potentiel( Vector3D(p.x+eps, p.y, p.z) ) - v,
                potentiel( Vector3D(p.x, p.y+eps, p.z) ) - v,
                potentiel( Vector3D(p.x, p.y, p.z+eps) ) - v);
  /*n += Vector3D(potentiel( Vector3D(p.x-eps, p.y, p.z) ) - v,
            potentiel( Vector3D(p.x, p.y-eps, p.z) ) - v,
            potentiel( Vector3D(p.x, p.y, p.z-eps) ) - v);*/
  return -n.normalized();
}
