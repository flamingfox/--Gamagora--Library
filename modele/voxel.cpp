#include "voxel.h"

Voxel::Voxel():_nbCubeParDimension(0), _posMin(0,0,0), _posMax(1,1,1){
}

Voxel::Voxel(const Vector3D &posMin, const Vector3D &posMax, const int &nbCubeParDimension):_nbCubeParDimension(nbCubeParDimension), _posMin(posMin), _posMax(posMax){
    v.resize(nbCubeParDimension*nbCubeParDimension*nbCubeParDimension);
}

/*
Voxel Voxel::operator +(const Voxel &v)
{
    Voxel retour;

    Vector3D posMin, posMax;

    if(v._posMin < this->_posMin)
        posMin = v._posMin;
    else
        posMin = this->_posMin;

    if(v._posMax > this->_posMax)
        posMax = v._posMax;
    else
        posMax = this->_posMax;


    float distanceDimensionX = posMax.x - posMin.x;
    Vector3D dimensionCubeUnitaire;

    if(v.getDimensionCubeUnitaire() < this->getDimensionCubeUnitaire())
        dimensionCubeUnitaire = v.getDimensionCubeUnitaire();
    else
        dimensionCubeUnitaire = this->getDimensionCubeUnitaire();

    int nbCubeParDimension = (int) (roundf(distanceDimensionX/dimensionCubeUnitaire.x));

    posMax = posMin + dimensionCubeUnitaire*nbCubeParDimension;

    retour = Voxel(posMin,posMax, nbCubeParDimension);

    Vector3D dimCubeUnitaire = retour.getDimensionCubeUnitaire();

    for(int i=0; i<nbCubeParDimension; i++){
        for(int j=0; j<nbCubeParDimension; j++){
            for(int k=0; k<nbCubeParDimension; k++){

                Vector3D tmp = retour.getPosMin();
                tmp.x += (i+0.5)*dimCubeUnitaire.x;
                tmp.y += (j+0.5)*dimCubeUnitaire.y;
                tmp.z += (k+0.5)*dimCubeUnitaire.z;

                if(v.getIndiceCase(tmp) != -1 && v.v[v.getIndiceCase(tmp)] != 0){
                    retour(i,j,k) = 1;
                }

                if(this->getIndiceCase(tmp) != -1 && this->v[this->getIndiceCase(tmp)] != 0){
                    retour(i,j,k) = 1;
                }
            }
        }
    }

    return retour;


}
*/

int Voxel::getIndiceCase(const Vector3D &position) const
{
    //Test hors zone voxel
    if(position < this->_posMin || position > this->_posMax){
        return -1;
    }

    float dimensionCubeUnitaire = (_posMax.x-_posMin.x)/_nbCubeParDimension;

    Vector3D positionRelative = position - _posMin;

    Vector3D indices = positionRelative / dimensionCubeUnitaire;

    int indiceZ = (int)(indices.z)*_nbCubeParDimension*_nbCubeParDimension;
    int indiceY = (int)(indices.y)*_nbCubeParDimension;
    int indiceX = (int)(indices.x);

    return (int)(indices.z)*_nbCubeParDimension*_nbCubeParDimension+(int)(indices.y)*_nbCubeParDimension+(int)(indices.x);
}
