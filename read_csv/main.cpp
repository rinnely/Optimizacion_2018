#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std; 

float getMatrix(std::string file_name,int rows,int cols);

const int rows = 10;
const int cols = 5;

int main(void) {
	
  	 float matrix = getMatrix("file.csv", rows, cols);
    //imprime matriz
    //for (int i = 0; i < rows; i++) {
      //  for (int j = 0; j < cols; j++) {
        //    printf("%f ", matrix[i][j]);
        //}
        //printf("\n");
    //}

    return 0;
}

float getMatrix(std::string file_name, int rows, int cols)
{
	float matrix[rows][cols];
	//lee el archivo
	FILE *file = fopen(file_name.c_str(),"r");
	int value;
	for(int i = 0; i < rows; i++)
	{
	 for(int j = 0; j < cols; j++)
	 {
	  fscanf(file, "%f", &matrix[i][j]);
	 }
	}
	return matrix;
}

