#include "objmanager.h"

Mesh ObjManager::loadFromOBJ(const Vector3D &center, const char* obj){

    Mesh retour;

    /*
    std::vector<Vector3D> geom;
    std::vector<Vector3D> normalsPoints;
    std::vector<int> topo;
    std::vector<int> normalIds; */

    Vector3D centreGravite;

    Vector3D minVal(1E100, 1E100, 1E100), maxVal(-1E100, -1E100, -1E100);
    FILE* f = fopen(obj, "r");
    while (!feof(f)) {
        char line[255];
        for(int i=0; i<255; i++) line[i]=0;

        fgets(line, 255, f);
        if (line[0]=='v' && line[1]==' ') {
            Vector3D vec;
            sscanf(line, "v %f %f %f\n", &vec[0], &vec[2], &vec[1]);
            vec[2] = -vec[2];
            Vector3D p = vec + center;
            retour.addVertex(p);
            maxVal[0] = std::max(maxVal[0], p[0]);
            maxVal[1] = std::max(maxVal[1], p[1]);
            maxVal[2] = std::max(maxVal[2], p[2]);
            minVal[0] = std::min(minVal[0], p[0]);
            minVal[1] = std::min(minVal[1], p[1]);
            minVal[2] = std::min(minVal[2], p[2]);

            centreGravite += p;
        }
        if (line[0]=='v' && line[1]=='n') {
            Vector3D vec;
            sscanf(line, "vn %f %f %f\n", &vec[0], &vec[2], &vec[1]);
            vec[2] = -vec[2];
            //normalsPoints.push_back(vec);
        }
        if (line[0]=='f') {
            int i0, i1, i2;
            int j0,j1,j2;
            int k0,k1,k2;

            int n = 0;
            //sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &i0, &j0, &k0, &i1, &j1, &k1, &i2, &j2, &k2 );

            //count of '/' occuration in the line
            for (int i=0; i < sizeof(line); i++){
                if(line[i]=='/')
                    n++;
            }

            if(n==0){
                sscanf(line, "f %u %u %u\n", &i0, &i1, &i2);

                retour.addFace(i0-1, i1-1, i2-1);
                //topo.push_back(i0-1);
                //topo.push_back(i1-1);
                //topo.push_back(i2-1);

            }
            else if(n==3){
                sscanf(line, "f %u/%u %u/%u %u/%u\n", &i0, &k0, &i1, &k1, &i2, &k2 );

                retour.addFace(i0-1, i1-1, i2-1);
                //topo.push_back(i0-1);
                //topo.push_back(i1-1);
                //topo.push_back(i2-1);
                //normalIds.push_back(k0-1);
                //normalIds.push_back(k1-1);
                //normalIds.push_back(k2-1);

            }
            else if(n==6){
                sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &i0, &j0, &k0, &i1, &j1, &k1, &i2, &j2, &k2 );

                retour.addFace(i0-1, i1-1, i2-1);
                //topo.push_back(i0-1);
                //topo.push_back(i1-1);
                //topo.push_back(i2-1);
                //normalIds.push_back(k0-1);
                //normalIds.push_back(k1-1);
                //normalIds.push_back(k2-1);
            }
        }
    }

    /*boundingSphere.C = 0.5*(minVal+maxVal);
    boundingSphere.R = sqrt((maxVal-minVal).sqrNorm())*0.5;*/

    fclose(f);

    //Mesh retour;

    /*
    if(!geom.empty() && !topo.empty()){
        //retour.setVertex(geom);
        retour.addVertex(geom);
        //retour.setFace(topo);
        retour.addFace(topo);
    }*/

    centreGravite /= retour.nbvertex();
    retour.translation(centreGravite.x, centreGravite.y, centreGravite.z);
    retour.rescale( 1/(maxVal-minVal).getNorm() );

    return retour;
}

void ObjManager::writeToObj(const std::string name, const std::vector<Vector3D> &vertex, const std::vector<unsigned int> &face)
{
    std::ofstream obj;
    obj.open(name.c_str(), std::ios::out);

    obj << "#vertices:\n";

    for(int i = 0 ; i < vertex.size(); i++) {
        obj << "v " << std::setprecision(4) << vertex[i].x << " " << vertex[i].y << " " << vertex[i].z << "\n";
    }

    obj << "#faces:\n";

    for(int i = 0 ; i < face.size(); i += 3){
        obj << "f " << face[i] + 1 << " " << face[i+1] + 1 << " "<< face[i+2] + 1 << "\n";

    }

    obj << "\n";

    obj.close();

    std::cout << "wrote " << name << std::endl;
}

void ObjManager::voxelSave(const std::string& name, const Voxel &vox){

    std::vector<Vector3D> vertex;
    std::vector<unsigned int> face;

    const float scale = 1.0/2.0;

    const unsigned int nb = vox.getNbCubeParDimension();
    for(unsigned int i=0; i<nb; i++){
        for(unsigned int j=0; j<nb; j++){
            for(unsigned int k=0; k<nb; k++){

                if(vox(i,j,k) != 0){

                    /*
                          (s7)       (s6)
                           x----------x
                          /          /|
                     (s3)/      (s2)/ |
                        x----------x  |
                        |      X   |  |
                        |  x(i,j,k)|  x (s5)
                        | (s4)     | /
                        |          |/
                        x----------x
                      (s0)        (s1)

                    */

                    // ajout faces
                    unsigned int s0 = vertex.size(), s1 = vertex.size()+1, s2 = vertex.size()+2, s3 = vertex.size()+3,
                            s4 = vertex.size()+4, s5 = vertex.size()+5, s6 = vertex.size()+6, s7 = vertex.size()+7;

                    vertex.push_back(Vector3D(i-scale,j-scale,k-scale));
                    vertex.push_back(Vector3D(i-scale,j-scale,k+scale));
                    vertex.push_back(Vector3D(i-scale,j+scale,k+scale));
                    vertex.push_back(Vector3D(i-scale,j+scale,k-scale));

                    vertex.push_back(Vector3D(i+scale,j-scale,k-scale));
                    vertex.push_back(Vector3D(i+scale,j-scale,k+scale));
                    vertex.push_back(Vector3D(i+scale,j+scale,k+scale));
                    vertex.push_back(Vector3D(i+scale,j+scale,k-scale));


                    if(i == 0 || vox(i-1,j,k) == 0){

                        //** Face s0,s1,s2,s3 **//
                        face.push_back(s0);
                        face.push_back(s1);
                        face.push_back(s3);

                        face.push_back(s3);
                        face.push_back(s1);
                        face.push_back(s2);
                    }

                    if(k == nb-1 || vox(i,j,k+1) == 0){
                        //** Face s1,s5,s6,s2 **//
                        face.push_back(s1);
                        face.push_back(s5);
                        face.push_back(s2);

                        face.push_back(s2);
                        face.push_back(s5);
                        face.push_back(s6);
                    }

                    if(i == nb-1 || vox(i+1,j,k) == 0){
                        //** Face s5,s4,s7,s6 **//
                        face.push_back(s5);
                        face.push_back(s4);
                        face.push_back(s6);

                        face.push_back(s6);
                        face.push_back(s4);
                        face.push_back(s7);

                    }

                    if(k == 0 || vox(i,j,k-1) == 0){
                        //** Face s4,s0,s3,s7 **//
                        face.push_back(s4);
                        face.push_back(s0);
                        face.push_back(s7);

                        face.push_back(s7);
                        face.push_back(s0);
                        face.push_back(s3);
                    }

                    if(j == 0 || vox(i,j-1,k) == 0){

                        //** Face s5,s4,s0,s1 **//
                        face.push_back(s5);
                        face.push_back(s4);
                        face.push_back(s1);

                        face.push_back(s1);
                        face.push_back(s4);
                        face.push_back(s0);
                    }

                    if(j == nb-1 || vox(i,j+1,k) == 0){

                        //** Face s3,s2,s6,s7 **//
                        face.push_back(s3);
                        face.push_back(s2);
                        face.push_back(s7);

                        face.push_back(s7);
                        face.push_back(s2);
                        face.push_back(s6);
                    }
                }
            }
        }
    }
    writeToObj(name, vertex, face);
}
