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

std::vector<point3> Mesh::getvertex() const{
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
	for(point3& p: vertex){
		p.x+=x;
		p.y+=y;
		p.z+=z;
	}
}

void Mesh::rescale(float scale)
{
	for(point3& p: vertex){
		p *= scale;
	}
}