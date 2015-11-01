#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include "geometrie/vector3d.h"
#include "modele/voxel.h"
#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>

namespace ObjManager
{
    void writeToObj(const std::string name, const std::vector<Vector3D>& vertex, const std::vector<unsigned int>& face);

    void voxelSave(const std::string &name, const Voxel& vox);
}

#endif // OBJMANAGER_H
