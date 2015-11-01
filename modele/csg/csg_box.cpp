#include "csg_box.h"

CSG_Box::CSG_Box(float cote):
    Box(glm::vec3(-cote/2,-cote/2,-cote/2), glm::vec3(cote/2,cote/2,cote/2))
{
}

CSG_Box::CSG_Box(const vec3& _min, const vec3& _max)    :
    Box(_min,_max)
{
}

bool CSG_Box::inOut(const vec3& p) const
{
    return Box::inOut(p);
}


bool CSG_Box::intersect(const Rayon &r, float &distanceMin) const
{
    float distanceMax;
    return Box::intersect(r, distanceMin, distanceMax);
}


float CSG_Box::distance(const vec3 &p) const
{
    return Box::distance(p);
}

/*float CSG_Box::distance(const vec3 &p) const
{
    float dx = min.x - p.x;
    if(p.x - max.x < dx)
        dx = p.x - max.x;

    float dy = min.y - p.y;
    if(p.y - max.y < dy)
        dy = p.y - max.y;

    float dz = min.z - p.z;
    if(p.z - max.z < dz)
        dz = p.z - max.z;*/


vec3 CSG_Box::getNormal(const vec3& p) const
{
    return Box::getNormal(p);
}
