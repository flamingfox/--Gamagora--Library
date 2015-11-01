#ifndef OBJMANAGER_H
#define OBJMANAGER_H

#include <glm/vec3.hpp>

#include "lib/voxel.h"
#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>

class ObjManager
{
public:
    ObjManager();

    static void voxelSave(const std::string &name, const Voxel& vox);

private:
    static void writeToObj(const std::string name, const std::vector<glm::vec3>& vertex, const std::vector<unsigned int>& face);

};

#endif // OBJMANAGER_H
