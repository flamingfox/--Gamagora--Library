#include "camera.h"
#include "geometrie/vector3d.h"

Camera::Camera()
{

}

/**
@pOr origine de la caméra
@pAt vecteur direction de la caméra (comprenant distance)
*/

Camera::Camera(const Vector3D &pOr, const Vector3D &pAt, const float &distance, int l, int h) :
    _origine(pOr), _lu(l), _lv(h), _lw(distance)
{
    Vector3D tmp(pAt - pOr);
    _w = tmp.normalized();

    if(_w == Vector3D(0.f,0.f,1.f) || _w == Vector3D(0.f,0.f,-1.f))
    {
        _u = Vector3D(_w.z,0.f,0.f);
        _v = Vector3D(0.f,_w.z,0.f);
    }
    else
    {
        _u = - ( _w.crossProduct(Vector3D(0.f,0.f,1.f)) );
        _u.normalize();

        _v = _w.crossProduct(_u);
        _v.normalize();
    }
}

Vector3D Camera::vecScreen(int i, int j) const
{
    if(i >= _lu || j >= _lv){
        std::cerr << "i or j is incorrect" << std::endl;
        exit(-1);
    }

    float ti = ((float)i) / (_lu - 1);
    float tj = ((float)j) / (_lv - 1);


    return _w*_lw + _u*( (-_lu/2)*(1.0f - ti)+(_lu/2*ti) ) + _v*( (1.0f-tj)*(_lv/2)+(tj*(-_lv/2)) );
}

Vector3D Camera::pointScreen(int i, int j) const
{
    return _origine + vecScreen(i, j);
}






