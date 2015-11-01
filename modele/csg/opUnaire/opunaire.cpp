#include "opunaire.h"

OpUnaire::OpUnaire(Node *a):
    a(a)
{
}

OpUnaire::~OpUnaire()
{
    //delete a;
}

bool OpUnaire::inOut(const Vector3D &p) const
{
    return a->inOut(deplace(p));
}
float OpUnaire::potentiel(const Vector3D &p) const
{
    return a->potentiel(deplace(p));
}

float OpUnaire::distance(const Vector3D &p) const
{
    return a->distance(deplace(p));
}
