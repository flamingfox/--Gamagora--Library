#include "si_box.h"

SI_Box::SI_Box(float cote, float e, float R):
        SI_Box(Vector3D(-cote/2,-cote/2,-cote/2),Vector3D(cote/2,cote/2,cote/2), e, R)
{
}

SI_Box::SI_Box(const Vector3D& min, const Vector3D& max, float e, float R):
        SI_Primitive(e,R), Box(min,max),    englob(Box(min-R,max+R))
{
}

float SI_Box::potentiel(const Vector3D& p) const
{
    Vector3D cote = (max-min)/2.f;

    Vector3D pos = Vector3D(fabsf(p.x - (min.x+cote.x)),
                            fabsf(p.y - (min.y+cote.y)),
                            fabsf(p.z - (min.z+cote.z)));
    float val = 0.0;

    if(pos.x > cote.x)
        val += (cote.x - pos.x)*(cote.x - pos.x);

    if(pos.y > cote.y)
        val += (cote.y - pos.y)*(cote.y - pos.y);

    if(pos.z > cote.z)
        val += (cote.z - pos.z)*(cote.z - pos.z);

    return e*falloff(val,R);
}

float SI_Box::distance(const Vector3D& p) const
{
    return englob.distance(p);
}
