#include "opr.h"

OpR::OpR(Node *a, const glm::vec3& axe, float angle):
    OpUnaire(a),   axe(axe),   angle(angle)
{
}

glm::vec3 OpR::deplace(const glm::vec3& p) const
{

    if(angle != 0)
        return rotate(p, -angle);
    else
        return p;
}

glm::vec3 OpR::rotate(const vec3& p, float angle) const
{
    glm::vec3 v;
        //axe2 = glm::normalize(axe);

        v.x =   axe.x*(axe.x*p.x + axe.y*p.y + axe.z*p.z) * (1-cos(angle))+
                p.x*cos(angle)+
                (-axe.z*p.y + axe.y*p.z) * sin(angle);
        v.y =   axe.y*(axe.x*p.x + axe.y*p.y + axe.z*p.z) * (1-cos(angle))+
                p.y*cos(angle)+
                (axe.z*p.x - axe.x*p.z) * sin(angle);
        v.z =   axe.z*(axe.x*p.x + axe.y*p.y + axe.z*p.z) * (1-cos(angle))+
                p.z*cos(angle)+
                (-axe.y*p.x + axe.x*p.y) * sin(angle);
    return v;
}

/*************************************************************************************/



/*bool OpR::intersect(const Rayon &r, float &distanceMin) const
{
    glm::vec3   o = r.getOrigine(),
                d = r.getDirection();

    if(angle != 0)
    {
        //axe2 = glm::normalize(axe);
        float x = o.x, y = o.y; //pour ne pas prendre la valeure modifiée dans les lignes suivantes (v.z = ...)

        o.x =   axe.x*(axe.x*x + axe.y*y + axe.z*o.z) * (1-cos(-angle))+
                x*cos(-angle)+
                (-axe.z*y + axe.y*o.z) * sin(-angle);
        o.y =   axe.y*(axe.x*x + axe.y*y + axe.z*o.z) * (1-cos(-angle))+
                y*cos(-angle)+
                (axe.z*x - axe.x*o.z) * sin(-angle);
        o.z =   axe.z*(axe.x*x + axe.y*y + axe.z*o.z) * (1-cos(-angle))+
                o.z*cos(-angle)+
                (-axe.y*x + axe.x*y) * sin(-angle);

        x = d.x, y = d.y;

        d.x =   axe.x*(axe.x*x + axe.y*y + axe.z*d.z) * (1-cos(-angle))+
                x*cos(-angle)+
                (-axe.z*y + axe.y*d.z) * sin(-angle);
        d.y =   axe.y*(axe.x*x + axe.y*y + axe.z*d.z) * (1-cos(-angle))+
                y*cos(-angle)+
                (axe.z*x - axe.x*d.z) * sin(-angle);
        d.z =   axe.z*(axe.x*x + axe.y*y + axe.z*d.z) * (1-cos(-angle))+
                d.z*cos(-angle)+
                (-axe.y*x + axe.x*y) * sin(-angle);
    }

    return a->intersect(Rayon(o,d), distanceMin);
}*/


vec3 OpR::getNormal(const vec3 &p, float eps) const
{
    vec3 n = a->getNormal(deplace(p), eps);
    if(angle != 0)
        n = rotate(n,angle);
    return n;
}
