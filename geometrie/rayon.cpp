#include "rayon.h"

Vector3D Rayon::Reflect(const Vector3D& normal) const {
    const float cosI = dot(normal,_direction);
    return _direction + normal * 2*cosI;
}
