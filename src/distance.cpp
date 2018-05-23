#include "DisplayImage.cpp"
#include <string>

using namespace std;
Display_image di;

// Import biomass and friction
string map_biomass = "biomass.tiff";
string map_friction = "friction.tiff";
float** biomass = di.tiff_to_matrix_gdal(map_biomass, true);
float** friction = di.tiff_to_matrix_gdal(map_friction, false);

void distanceMatrix(float** biomass, float** friction, int X, int Y){
  float** cost;
  vecinos(X,Y,cost,biomass,friction);

  
}

float** getDistance(float** biomass, float** friction, int* centroidesX, int* centroidesY, int N){
  #pragma paralel for
    for(int i = 0; i < N; ++i){
      distanceMatrix(biomass,friction,centroidesX[i],centroidesY[i]);
    }
}
