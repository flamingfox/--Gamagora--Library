#include "quadrangle.h"


float Quadrangle::area() const
{
    /*
     * A=1/2*d1*d2*sin(alpha)
     *
     * http://onlinemschool.com/math/formula/area/#h5
     *
     */

    Vector2D d1 = p3-p1, d2 = p4-p2;

    float alpha = acosf(d1.scalareProduct(d2)/d1.getNorm());

    return (1/2)*d1.getNorm()*d2.getNorm()*sin(alpha);
}

float Quadrangle::perimetre() const
{
    return (p2-p1).getNorm()+(p3-p2).getNorm()+(p4-p3).getNorm()+(p1-p4).getNorm();
}

void Quadrangle::shrink(const float &l)
{

    Vector2D tab[4];

    for(int i=0; i<4; i++){
        Vector2D orth1 = Orthogonal(-((*this)[(i+1)%4]-(*this)[i])).normalise();
        Vector2D orth2 = Orthogonal( ((*this)[(i-1)%4]-(*this)[i])).normalise();

        std::cout << (*this)[i] << " :: " << (*this)[(i+1)%4] << std::endl;
        std::cout << (*this)[(i+1)%4]-(*this)[i] << std::endl;
        std::cout << "orth1 : " << orth1 << std::endl;

        std::cout << (*this)[i] << " :: " << (*this)[(i-1)%4] << std::endl;
        std::cout << ((*this)[(i-1)%4]-(*this)[i]) << std::endl;
        std::cout << "orth2 : " << orth2 << std::endl;
        std::cout << "tab["<<i<<"] : " << tab[i] << std::endl;

        Vector2D v = (orth1 + orth2)/2;

        std::cout << "v.Norm() : " << v.getNorm() << std::endl;
        std::cout << std::endl;

        tab[i] = (*this)[i]+Normalized(v)*(l/(v.getNorm()));
    }

    for(int i=0; i<4; i++){
        std::cout << "tab["<<i<<"] : " << tab[i] << std::endl;
        (*this)[i] = tab[i];
    }
}
