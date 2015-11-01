#include "opunaire.h"

OpUnaire::OpUnaire(Node *a):
    a(a)
{
}

OpUnaire::~OpUnaire()
{
    //delete a;
}

bool OpUnaire::inOut(const glm::vec3 &p) const
{
    return a->inOut(deplace(p));
}
float OpUnaire::potentiel(const glm::vec3 &p) const
{
    return a->potentiel(deplace(p));
}

float OpUnaire::distance(const glm::vec3 &p) const
{
    return a->distance(deplace(p));
}
