#include "opbin.h"

OpBin::OpBin(Node* _a, Node* _b) :
    a(_a), b(_b)
{

}

OpBin::~OpBin()
{
    //delete a;
    //delete b;
}

float OpBin::distance(const Vector3D &p) const
{
    return std::min(a->distance(p) , b->distance(p));
}
