	#include "DisplayImage.cpp"
  Display_image di;

	// Import biomass and friction
  str map_biomass = "nombre_de_la_archivo"
	clock_t begin = clock();
	float** biomass = di.tiff_to_matrix_gdal(map_biomass, true);
	float** friction = di.tiff_to_matrix_gdal(map_friction, false);
