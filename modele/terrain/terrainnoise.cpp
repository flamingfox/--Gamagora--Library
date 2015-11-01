#include "terrainnoise.h"

TerrainNoise::TerrainNoise() : Terrain()
{}

TerrainNoise::TerrainNoise(int _longueur, int _largeur) :
    Terrain(_longueur, _largeur)
{
    hauteurMin = minElevation();
    hauteurMax = maxElevation();
    box.updatePoint(Vector3D(0,0,hauteurMax));
}


/**
 * @param x abscisse du terrain (entre 0 et largeur)
 * @param y ordonnée du terrain (entre 0 et longueur)
 * @return la hauteur du terrain à ses coordonnées x, y
*/
float TerrainNoise::getHauteur(float x, float y) const
{
    if(x < 0 || y < 0 || x > largeur || y > longueur)
            return HAUTEUR_HORS_MAP;

    return getHauteur2(x,y);    //inline
}

/**
 * @brief Retourne la hauteur du terrain aux coordonnées (x,y). \n
 * Ne vérifie pas que l'on est en dehors du terrain. \n
 * Utile pour avoir une bonne normal sur les bords du terrain.
 * @param x abscisse du terrain (entre 0 et largeur)
 * @param y ordonnée du terrain (entre 0 et longueur)
 * @return la hauteur du terrain à ses coordonnées x, y
 */
inline float TerrainNoise::getHauteur2(float x, float y) const
{
    nrw::warp(x,y, 50 ,350);
    float h = nrw::noise(400,300,x,y);

    h = nrw::ridge(h, 250);

    float h2 = nrw::noise(100, 100, x, y);

    h -= h2*nrw::attenuation(h,50,200);

    float h3 = nrw::noise(50,30,x,y);
    h += h3*nrw::attenuation(h,50,200);

    return h;
}

Vector3D TerrainNoise::getNormal(float x, float y, float eps) const
{

    float   ha = getHauteur2(x,y);
    float   g = getHauteur2(x-eps,y),
            d = getHauteur2(x+eps,y),
            b = getHauteur2(x,y+eps),
            h = getHauteur2(x,y-eps);
    Vector3D        vg(-eps, 0, g-ha),
                vd(eps, 0, d-ha),
                vb(0, eps, b-ha),
                vh(0, -eps, h-ha);
    float   distg = vg.length(),
            distd = vd.length(),
            distb = vb.length(),
            disth = vh.length();
    Vector3D        v1 = vg.crossProduct(vh),
                v2 = vh.crossProduct(vd),
                v3 = vd.crossProduct(vb),
                v4 = vb.crossProduct(vg);
    v1 = v1.normalized();
    v2 = v2.normalized();
    v3 = v3.normalized();
    v4 = v4.normalized();
    Vector3D normale = v1*distg*disth + v2*disth*distd + v3*distd*distb + v4*distb*distg;
    return normale.normalized();
}



float TerrainNoise::minElevation() const{
    float hMin = FLT_MAX;
    float hauteur;
    #pragma omp parallel for schedule(dynamic,1)
    for(int y = 0 ; y<(int)longueur; y++){
        for(int x = 0; x<largeur; x++){
            hauteur = getHauteur(x,y);
            if(hauteur<hMin)hMin=hauteur;
        }
    }
    return hMin;
}

float TerrainNoise::maxElevation() const{
    float hMax = FLT_MIN;
    float hauteur;
    #pragma omp parallel for schedule(dynamic,1)
    for(int y = 0 ; y<(int)longueur; y++){
        for(int x = 0; x<largeur; x++){
            hauteur = getHauteur(x,y);
            if(hauteur>hMax)hMax=hauteur;
        }
    }
    return hMax;
}

