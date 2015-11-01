#include "voxel.h"

Voxel::Voxel():_n(0){
}

Voxel::Voxel(int n):_n(n){
    v.resize(n*n*n);
}

