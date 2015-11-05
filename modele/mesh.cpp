#include "mesh.h"


/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            Fonctions utilitaires             */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

void Mesh::merge(const Mesh &delta)
{
	if(&delta != this){
		int taille = vertex.size();
		vertex.reserve(taille+delta.nbvertex());

		for(size_t i=0; i< delta.vertex.size(); i++){
			vertex.push_back(delta.vertex[i]);
		}

		face.reserve(this->nbface()+delta.nbface());
		for(size_t i=0; i< delta.face.size(); i++){
			face.push_back(delta.face[i] + taille );
		}
	}
}

/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */
/*            Fonctions accessors               */
/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

std::vector<Vector3D> Mesh::getvertex() const{
	return vertex;
}

std::vector<int> Mesh::getface() const{
	return face;
}

size_t Mesh::nbvertex() const
{
	return this->vertex.size();
}

size_t Mesh::nbface() const
{
	return this->face.size();
}


void Mesh::translation(const float x, const float y, const float z)
{
	for(Vector3D& p: vertex){
		p.x+=x;
		p.y+=y;
		p.z+=z;
	}
}

void Mesh::rescale(float scale)
{
	for(Vector3D& p: vertex){
		p *= scale;
	}
}

void Mesh::rotation(const Vector3D T){
    Rotation(T.x, T.y, T.z);
}

void Mesh::rotation(const float rX, const float rY, const float rZ){

    for(size_t i=0; i<geom.size(); i++){
        if(rX != 0)
			geom[i].rotateAboutAxis(rX, Vector3D(1,0,0) );
		if(rY != 0)
			geom[i].rotateAboutAxis(rY, Vector3D(0,1,0) );
		if(rZ != 0)
			geom[i].rotateAboutAxis(rZ, Vector3D(0,0,1) );
    }
}