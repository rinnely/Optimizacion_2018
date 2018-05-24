#include "DisplayImage.cpp"
#include "distance.cpp"
#include <string>
#include <stdio.h>
#include <omp.h>

using namespace std;
Display_image di;

// Import biomass and friction
string map_biomass = "biomass.tiff";
string map_friction = "friction.tiff";

float** biomass = di.tiff_to_matrix_gdal(map_biomass, true);
float** friction = di.tiff_to_matrix_gdal(map_friction, false);

int rows = di.ROWS;
int cols = di.COLS;

void main(){
    #pragma omp for collapse(2)
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (biomass[x][y] > 0){
                    output_ raster = getDistance(biomass, friction, int x, int y, int rows, int cols, di.intervals, i - 80, i + 80, j - 80, j + 80);
                }
            }
        }
}

