#include "opr.h"

OpR::OpR(Node *a, const Vector3D& axe, float angle):
    OpUnaire(a),   axe(axe),   angle(angle)
{
}

Vector3D OpR::deplace(const Vector3D& p) const
{

    if(angle != 0)
        return rotate(p, -angle);
    else
        return p;
}

Vector3D OpR::rotate(const Vector3D& p, float angle) const
{
    Vector3D v;
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
    Vector3D   o = r.getOrigine(),
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


Vector3D OpR::getNormal(const Vector3D &p, float eps) const
{
    Vector3D n = a->getNormal(deplace(p), eps);
    if(angle != 0)
        n = rotate(n,angle);
    return n;
}
