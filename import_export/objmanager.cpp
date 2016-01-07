#include "objmanager.h"

Mesh loadFromOBJ(const glm::vec3 &center, const char* obj){
    glm::vec3 minVal(1E100, 1E100, 1E100), maxVal(-1E100, -1E100, -1E100);
    FILE* f = fopen(obj, "r");
    while (!feof(f)) {
        char line[255];
        fgets(line, 255, f);
        if (line[0]=='v' && line[1]==' ') {
            glm::vec3 vec;
            sscanf(line, "v %lf %lf %lf\n", &vec[0], &vec[2], &vec[1]);
            vec[2] = -vec[2];
            glm::vec3 p = vec*50.f + center;
            geom.push_back(p);
            maxVal[0] = std::max(maxVal[0], p[0]);
            maxVal[1] = std::max(maxVal[1], p[1]);
            maxVal[2] = std::max(maxVal[2], p[2]);
            minVal[0] = std::min(minVal[0], p[0]);
            minVal[1] = std::min(minVal[1], p[1]);
            minVal[2] = std::min(minVal[2], p[2]);
        }
        if (line[0]=='v' && line[1]=='n') {
            glm::vec3 vec;
            sscanf(line, "vn %lf %lf %lf\n", &vec[0], &vec[2], &vec[1]);
            vec[2] = -vec[2];
            normalsPoints.push_back(vec);
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

                topo.push_back(i0-1);
                topo.push_back(i1-1);
                topo.push_back(i2-1);

            }
            else if(n==3){
                sscanf(line, "f %u/%u %u/%u %u/%u\n", &i0, &k0, &i1, &k1, &i2, &k2 );

                topo.push_back(i0-1);
                topo.push_back(i1-1);
                topo.push_back(i2-1);
                normalIds.push_back(k0-1);
                normalIds.push_back(k1-1);
                normalIds.push_back(k2-1);

            }
            else if(n==6){
                sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &i0, &j0, &k0, &i1, &j1, &k1, &i2, &j2, &k2 );

                topo.push_back(i0-1);
                topo.push_back(i1-1);
                topo.push_back(i2-1);
                normalIds.push_back(k0-1);
                normalIds.push_back(k1-1);
                normalIds.push_back(k2-1);
            }
        }
    }

    /*boundingSphere.C = 0.5*(minVal+maxVal);
    boundingSphere.R = sqrt((maxVal-minVal).sqrNorm())*0.5;*/

    fclose(f);
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

void ObjManager::voxelSave(const std::string& name, const Voxel &vox)
{
    std::vector<Vector3D> vertex;
    std::vector<unsigned int> face;

    /*
          (s7)       (s6)
           x----------x
          /          /|
     (s3)/      (s2)/ |
        x----------x  |
        |          |  |
        |  x       |  x (s5)
        | (s4)     | /
        |          |/
        x----------x
      (s0)        (s1)


      v.at(i*_n*_n+j*_n+k)

    */

    for(unsigned int i=0; i<vox.get_n(); i++){
        for(unsigned int j=0; j<vox.get_n(); j++){
            for(unsigned int k=0; k<vox.get_n(); k++){
                // ajout vertex
                vertex.push_back(Vector3D(i,j,k));
            }
        }
    }


    for(unsigned int i=0; i<vox.get_n()-1; i++){
        for(unsigned int j=0; j<vox.get_n()-1; j++){
            for(unsigned int k=0; k<vox.get_n()-1; k++){

                // ajout faces
                unsigned int s0 = vox(i,j,k), s1 = vox(i,j,k+1), s2 = vox(i,j+1,k+1), s3 = vox(i,j+1,k),
                        s4 = vox(i+1,j,k), s5 = vox(i+1,j,k+1), s6 = vox(i+1,j+1,k+1), s7 = vox(i+1,j+1,k);

                unsigned int indS0 = i*vox.get_n()*vox.get_n() + j*vox.get_n()+ k,
                        indS1 = i*vox.get_n()*vox.get_n() + j*vox.get_n()+ k+1,
                        indS2 = i*vox.get_n()*vox.get_n() + (j+1)*vox.get_n()+ k+1,
                        indS3 = i*vox.get_n()*vox.get_n() + (j+1)*vox.get_n()+ k,
                        indS4 = (i+1)*vox.get_n()*vox.get_n() + j*vox.get_n()+ k,
                        indS5 = (i+1)*vox.get_n()*vox.get_n() + j*vox.get_n()+ k+1,
                        indS6 = (i+1)*vox.get_n()*vox.get_n() + (j+1)*vox.get_n()+ k+1,
                        indS7 = (i+1)*vox.get_n()*vox.get_n() + (j+1)*vox.get_n()+ k;


                //** Face s0,s1,s2,s3 **//
                if( s0 != 0 ){
                    if( s1 != 0 ){
                        if( s2 != 0 ){
                            face.push_back(indS0);
                            face.push_back(indS1);
                            face.push_back(indS2);
                        }
                        else if( s3 != 0){
                            face.push_back(indS0);
                            face.push_back(indS1);
                            face.push_back(indS3);
                        }
                    }

                    if(s2 !=0 && s3 != 0){
                        face.push_back(indS0);
                        face.push_back(indS2);
                        face.push_back(indS3);
                    }
                }
                else if(s1 != 0 && s2 != 0 && s3 != 0){
                    face.push_back(indS1);
                    face.push_back(indS2);
                    face.push_back(indS3);
                }

                //** Face s4,s0,s3,s7 **//

                if( s4 != 0 ){
                    if( s0 != 0 ){
                        if( s3 != 0 ){
                            face.push_back(indS4);
                            face.push_back(indS0);
                            face.push_back(indS3);
                        }
                        else if( s7 != 0){
                            face.push_back(indS4);
                            face.push_back(indS0);
                            face.push_back(indS7);
                        }
                    }

                    if(s3 !=0 && s7 != 0){
                        face.push_back(indS4);
                        face.push_back(indS3);
                        face.push_back(indS7);
                    }
                }
                else if(s0 != 0 && s3 != 0 && s7 != 0){
                    face.push_back(indS0);
                    face.push_back(indS3);
                    face.push_back(indS7);
                }


                //** Face s4,s5,s1,s0 **//

                if( s4 != 0 ){
                    if( s5 != 0 ){
                        if( s1 != 0 ){
                            face.push_back(indS4);
                            face.push_back(indS5);
                            face.push_back(indS1);
                        }
                        else if( s0 != 0){
                            face.push_back(indS4);
                            face.push_back(indS5);
                            face.push_back(indS0);
                        }
                    }

                    if(s1 !=0 && s0 != 0){
                        face.push_back(indS4);
                        face.push_back(indS1);
                        face.push_back(indS0);
                    }
                }
                else if(s5 != 0 && s1 != 0 && s0 != 0){
                    face.push_back(indS5);
                    face.push_back(indS1);
                    face.push_back(indS0);
                }


                //** Cas particulier **//
                //**** Tronquer 1 sommet ****//

                if(s0 == 0 && s4 != 0 && s1 != 0 && s3 != 0){
                    face.push_back(indS4);
                    face.push_back(indS1);
                    face.push_back(indS3);
                }

                if(s1 == 0 && s0 != 0 && s5 != 0 && s2 != 0){
                    face.push_back(indS0);
                    face.push_back(indS5);
                    face.push_back(indS2);
                }

                if(s2 == 0 && s0 != 0 && s5 != 0 && s6 != 0){
                    face.push_back(indS0);
                    face.push_back(indS5);
                    face.push_back(indS6);
                }

                if(s3 == 0 && s4 != 0 && s2 != 0 && s7 != 0){
                    face.push_back(indS4);
                    face.push_back(indS2);
                    face.push_back(indS7);
                }

                if(s4 == 0 && s5 != 0 && s0 != 0 && s7 != 0){
                    face.push_back(indS5);
                    face.push_back(indS0);
                    face.push_back(indS7);
                }

                if(s5 == 0 && s1 != 0 && s4 != 0 && s6 != 0){
                    face.push_back(indS1);
                    face.push_back(indS4);
                    face.push_back(indS6);
                }

                if(s6 == 0 && s5 != 0 && s7 != 0 && s2 != 0){
                    face.push_back(indS5);
                    face.push_back(indS7);
                    face.push_back(indS2);
                }

                if(s7 == 0 && s4 != 0 && s3 != 0 && s6 != 0){
                    face.push_back(indS4);
                    face.push_back(indS3);
                    face.push_back(indS6);
                }

                //**** Tronquer 2~3 sommets ****//
                if(s0 == 0 ){
                    if( s1 == 0 ){
                        if(s5 != 0){
                            if(s4 != 0 && s3 != 0){
                                face.push_back(indS4);
                                face.push_back(indS5);
                                face.push_back(indS3);
                            }
                            if(s3 != 0 && s2 != 0){
                                face.push_back(indS3);
                                face.push_back(indS5);
                                face.push_back(indS2);
                            }
                        }
                        else if(s4 != 0){
                            if( s3 != 0 && s2 != 0){
                                face.push_back(indS3);
                                face.push_back(indS4);
                                face.push_back(indS2);
                            }
                            if(s2 != 0 && s5 != 0){
                                face.push_back(indS2);
                                face.push_back(indS4);
                                face.push_back(indS5);
                            }
                        }
                    }
                    if(s3 == 0 ){
                        if(s1 != 0){
                            if(s4 != 0 && s7 != 0){
                                face.push_back(indS4);
                                face.push_back(indS1);
                                face.push_back(indS7);
                            }
                            if(s7 != 0 && s2 != 0){
                                face.push_back(indS7);
                                face.push_back(indS1);
                                face.push_back(indS2);
                            }
                        }
                        else if(s4 != 0){
                            if(s7 != 0 && s2 != 0){
                                face.push_back(indS7);
                                face.push_back(indS4);
                                face.push_back(indS2);
                            }
                            if(s2 != 0 && s1 != 0){
                                face.push_back(indS2);
                                face.push_back(indS4);
                                face.push_back(indS1);
                            }
                        }
                    }
                    if(s4 == 0){
                        if(s1 != 0){
                            if(s3 != 0 && s7 != 0){
                                face.push_back(indS3);
                                face.push_back(indS1);
                                face.push_back(indS7);
                            }
                            if(s7 != 0 && s5 != 0){
                                face.push_back(indS7);
                                face.push_back(indS1);
                                face.push_back(indS5);
                            }
                        }
                        else if(s5 != 0){
                            if(s1 != 0 && s3 != 0){
                                face.push_back(indS1);
                                face.push_back(indS5);
                                face.push_back(indS3);
                            }
                            if(s3 != 0 && s7 != 0){
                                face.push_back(indS3);
                                face.push_back(indS5);
                                face.push_back(indS7);
                            }
                        }
                    }
                }

                if(s1 == 0 ){
                    if( s2 == 0 ){
                        if(s5 != 0){
                            if(s0 != 0 && s3 != 0){
                                face.push_back(indS0);
                                face.push_back(indS5);
                                face.push_back(indS3);
                            }
                            if(s3 != 0 && s6 != 0){
                                face.push_back(indS3);
                                face.push_back(indS5);
                                face.push_back(indS6);
                            }
                        }
                        else if(s6 != 0){
                            if(s5 != 0 && s0 != 0){
                                face.push_back(indS5);
                                face.push_back(indS6);
                                face.push_back(indS0);
                            }
                            if(s0 != 0 && s3 != 0){
                                face.push_back(indS0);
                                face.push_back(indS6);
                                face.push_back(indS3);
                            }
                        }
                    }
                    if(s5 == 0 ){
                        if(s4 != 0){
                            if(s6 != 0 && s2 != 0){
                                face.push_back(indS6);
                                face.push_back(indS4);
                                face.push_back(indS2);
                            }
                            if(s2 != 0 && s0 != 0){
                                face.push_back(indS2);
                                face.push_back(indS4);
                                face.push_back(indS0);
                            }
                        }
                        else if(s0 != 0){
                            if(s4 != 0 && s6 != 0){
                                face.push_back(indS4);
                                face.push_back(indS0);
                                face.push_back(indS6);
                            }
                            if(s6 != 0 && s2 != 0){
                                face.push_back(indS6);
                                face.push_back(indS0);
                                face.push_back(indS2);
                            }
                        }
                    }
                }

                if(s2 == 0 ){
                    if( s3 == 0 ){
                        if(s0 != 0){
                            if(s7 != 0 && s6 != 0){
                                face.push_back(indS7);
                                face.push_back(indS0);
                                face.push_back(indS6);
                            }
                            if(s6 != 0 && s1 != 0){
                                face.push_back(indS6);
                                face.push_back(indS0);
                                face.push_back(indS1);
                            }
                        }
                        else if(s1 != 0){
                            if(s0 != 0 && s7 != 0){
                                face.push_back(indS0);
                                face.push_back(indS1);
                                face.push_back(indS7);
                            }
                            if(s7 != 0 && s6 != 0){
                                face.push_back(indS7);
                                face.push_back(indS1);
                                face.push_back(indS6);
                            }
                        }
                    }
                    if(s6 == 0 ){
                        if(s5 != 0){
                            if(s1 != 0 && s3 != 0){
                                face.push_back(indS1);
                                face.push_back(indS5);
                                face.push_back(indS3);
                            }
                            if(s3 != 0 && s7 != 0){
                                face.push_back(indS3);
                                face.push_back(indS5);
                                face.push_back(indS7);
                            }
                        }
                        else if(s1 != 0){
                            if(s3 != 0 && s7 != 0){
                                face.push_back(indS3);
                                face.push_back(indS1);
                                face.push_back(indS7);
                            }
                            if(s7 != 0 && s5 != 0){
                                face.push_back(indS7);
                                face.push_back(indS1);
                                face.push_back(indS5);
                            }
                        }
                    }
                }

                if(s3 == 0 ){
                    if( s7 == 0 ){
                        if(s4 != 0){
                            if(s6 != 0 && s2 != 0){
                                face.push_back(indS6);
                                face.push_back(indS4);
                                face.push_back(indS2);
                            }
                            if(s2 != 0 && s0 != 0){
                                face.push_back(indS2);
                                face.push_back(indS4);
                                face.push_back(indS0);
                            }
                        }
                        else if(s0 != 0){
                            if(s4 != 0 && s6 != 0){
                                face.push_back(indS4);
                                face.push_back(indS0);
                                face.push_back(indS6);
                            }
                            if(s6 != 0 && s2 != 0){
                                face.push_back(indS6);
                                face.push_back(indS0);
                                face.push_back(indS2);
                            }
                        }
                    }
                }

                if(s4 == 0 ){
                    if( s7 == 0 ){
                        if(s0 != 0){
                            if(s5 != 0 && s6 != 0){
                                face.push_back(indS5);
                                face.push_back(indS0);
                                face.push_back(indS6);
                            }
                            if(s6 != 0 && s3 != 0){
                                face.push_back(indS6);
                                face.push_back(indS0);
                                face.push_back(indS3);
                            }
                        }
                        else if(s5 != 0){
                            if(s6 != 0 && s3 != 0){
                                face.push_back(indS6);
                                face.push_back(indS5);
                                face.push_back(indS3);
                            }
                            if(s3 != 0 && s0 != 0){
                                face.push_back(indS3);
                                face.push_back(indS5);
                                face.push_back(indS0);
                            }
                        }
                    }

                    if( s5 == 0 ){
                        if(s0 != 0){
                            if(s1 != 0 && s6 != 0){
                                face.push_back(indS1);
                                face.push_back(indS0);
                                face.push_back(indS6);
                            }
                            if(s6 != 0 && s7 != 0){
                                face.push_back(indS6);
                                face.push_back(indS0);
                                face.push_back(indS7);
                            }
                        }
                        else if(s1 != 0){
                            if(s6 != 0 && s7 != 0){
                                face.push_back(indS6);
                                face.push_back(indS1);
                                face.push_back(indS7);
                            }
                            if(s7 != 0 && s0 != 0){
                                face.push_back(indS7);
                                face.push_back(indS1);
                                face.push_back(indS0);
                            }
                        }
                    }
                }

                if(s5 == 0 ){
                    if( s6 == 0 ){
                        if(s1 != 0 ){
                            if(s4 != 0 && s7 != 0){
                                face.push_back(indS4);
                                face.push_back(indS1);
                                face.push_back(indS7);
                            }
                            if(s7 != 0 && s2 != 0){
                                face.push_back(indS7);
                                face.push_back(indS1);
                                face.push_back(indS2);
                            }
                        }
                        else if(s4 != 0){
                            if(s7 != 0 && s2 != 0){
                                face.push_back(indS7);
                                face.push_back(indS4);
                                face.push_back(indS2);
                            }
                            if(s2 != 0 && s1 != 0){
                                face.push_back(indS2);
                                face.push_back(indS4);
                                face.push_back(indS1);
                            }
                        }
                    }
                }

                if(s6 == 0 ){
                    if( s7 == 0 ){
                        if(s4 != 0){
                            if(s5 != 0 && s2 != 0){
                                face.push_back(indS5);
                                face.push_back(indS4);
                                face.push_back(indS2);
                            }
                            if(s2 != 0 && s3 != 0){
                                face.push_back(indS2);
                                face.push_back(indS4);
                                face.push_back(indS3);
                            }
                        }
                        else if(s5 != 0){
                            if(s2 != 0 && s3 != 0){
                                face.push_back(indS2);
                                face.push_back(indS5);
                                face.push_back(indS3);
                            }
                            if(s3 != 0 && s4 != 0){
                                face.push_back(indS3);
                                face.push_back(indS5);
                                face.push_back(indS4);
                            }
                        }
                    }
                }

                //**** Tronquer 4 sommets ****//

                if(s0 == 0 && s3 == 0 && s4 == 0 && s1 == 0
                        && s7 != 0 && s5 != 0 && s2 != 0){
                    face.push_back(indS7);
                    face.push_back(indS5);
                    face.push_back(indS2);
                }

                if(s1 == 0 && s0 == 0 && s2 == 0 && s5 == 0
                        && s3 != 0 && s4 != 0 && s6 != 0){
                    face.push_back(indS3);
                    face.push_back(indS4);
                    face.push_back(indS6);
                }

                if(s2 == 0 && s1 == 0 && s3 == 0 && s6 == 0
                        && s7 != 0 && s0 != 0 && s5 != 0){
                    face.push_back(indS7);
                    face.push_back(indS0);
                    face.push_back(indS5);
                }

                if(s3 == 0 && s0 == 0 && s2 == 0 && s7 == 0
                        && s4 != 0 && s1 != 0 && s6 != 0){
                    face.push_back(indS4);
                    face.push_back(indS1);
                    face.push_back(indS6);
                }

                if(s4 == 0 && s0 == 0 && s7 == 0 && s5 == 0
                        && s6 != 0 && s3 != 0 && s1 != 0){
                    face.push_back(indS6);
                    face.push_back(indS3);
                    face.push_back(indS1);
                }

                if(s5 == 0 && s4 == 0 && s3 == 0 && s6 == 0
                        && s2 != 0 && s0 != 0 && s7 != 0){
                    face.push_back(indS2);
                    face.push_back(indS0);
                    face.push_back(indS7);
                }

                if(s6 == 0 && s7 == 0 && s2 == 0 && s5 == 0
                        && s1 != 0 && s4 != 0 && s3 != 0){
                    face.push_back(indS1);
                    face.push_back(indS4);
                    face.push_back(indS3);
                }

                if(s7 == 0 && s3 == 0 && s4 == 0 && s6 == 0
                        && s5 != 0 && s0 != 0 && s2 != 0){
                    face.push_back(indS5);
                    face.push_back(indS0);
                    face.push_back(indS2);
                }
            }
        }
    }

    writeToObj(name, vertex, face);
}
