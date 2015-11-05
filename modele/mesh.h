#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <math.h>
#include "float.h"

#include "geometrie/vector3D"

#include <algorithm>

class Mesh{

protected:
    std::vector<Vector3D> vertex;
    std::vector<Vector3D> normalsPoints;
    std::vector<int> face;

public :

    Mesh(){}
    Mesh(std::vector<Vector3D> listvertex, std::vector<int> listface): vertex(listvertex), face(listface)  {}

    ~Mesh(){}

    void merge(const Mesh &delta);

    std::vector<Vector3D> getvertex() const;
    std::vector<int> getface() const;
    void setvertex(std::vector<Vector3D> vertex);
    void setface(std::vector<int> face);
    size_t nbvertex() const;
    size_t nbface() const;

	void translation(const float x, const float y, const float z);
	void rescale(float scale);

	void rotation(const Vector3D T);
	void rotation(const float rX, const float rY, const float rZ);
	
protected:

};


#endif // MESH_H
