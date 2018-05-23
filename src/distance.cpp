#include "DisplayImage.cpp"
#include <string>

using namespace std;
Display_image di;

// Import biomass and friction
string map_biomass = "biomass.tiff";
string map_friction = "friction.tiff";
float** biomass = di.tiff_to_matrix_gdal(map_biomass, true);
float** friction = di.tiff_to_matrix_gdal(map_friction, false);
