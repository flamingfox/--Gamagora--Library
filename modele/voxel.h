#ifndef VOXEL_H
#define VOXEL_H
#include "vector"
class Voxel
{
public:
    Voxel();
    Voxel(int n);

    int operator()(int i, int j, int k)const{return v.at(i*_n*_n+j*_n+k);}
    int& operator()(int i, int j, int k){return v[i*_n*_n+j*_n+k];}
    inline int get_n()const{return _n;}

private:
    std::vector<int>v;
    int _n;
};

#endif // VOXEL_H
