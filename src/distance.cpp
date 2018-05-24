#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
#include <set>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct cell {
    int x, y;
    float distance;
    cell(int x, int y, float distance) :
            x(x), y(y), distance(distance) {}
};

bool isInsideGrid(int i, int j, float* cost_raster){
    return (i >= 0 && i < ROW && j >= 0 && j < COL && cost_raster[i][j] >= 0);
}

set<cell> vecinos(int origen_x, int origen_y, int rows, int cols, float* cost_raster){

    set<cell>distancias;

    float** dis;
    dis = new float*[rows];

    for(int i = 0; i< rows; ++i)
        dis[i] = new float[cols];

    // initializing distance array by INT_MAX
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++){
            dis[i][j] = INT_MAX;
        }

    // direction arrays for simplification of getting
    // neighbour
    int dx[] = { -1, -1, 0, 1, 1, 1, 0,-1 };
    int dy[] = {  0,  1, 1, 1, 0, -1, -1,-1 };

    set<cell> st;

    // insert (0, 0) cell with 0 distance
    st.insert(cell(origen_x, origen_y, 0));

    // initialize distance of (0, 0) with its grid value
    dis[origen_x][origen_y] = cost_raster[origen_x][origen_y];

    // get the cell with minimum distance and delete
    // it from the set
    cell k = *st.begin();
    st.erase(st.begin());
    int x, y;
    // looping through all neighbours
    for (int i = 0; i < 8; i++){
        x = k.x + dx[i];
        y = k.y + dy[i];
        //cout << "x = " << x << " y = " << y << endl;
        // if not inside boundry, ignore them
        if (!isInsideGrid(x, y, cost_raster)){
            //cout << "no inside grid" << endl;
            continue;
        }

        if(i % 2 == 0){//par = no es diagonal
            //cout << "N" << endl;
            dis[x][y] = (dis[k.x][k.y] + cost_raster[x][y])/2;
        }
        else{
            //cout << "D" << endl;
            dis[x][y] = 1.414214*(dis[k.x][k.y] + cost_raster[x][y])/2;
        }
        distancias.insert(cell(x, y, dis[x][y]));
        active_raster[x][y] = true;
        output_raster[x][y] = dis[x][y];//son los bordes, no hay necesidad de verificar si es menor al INT_MAX
    }

    output_raster[origen_x][origen_y] = 0;

    for(int m=0; m<rows; m++)
        delete[] dis[m];

    st.clear();
    return distancias;
}

float* acumulados(set<cell> active_costs, int origen_x, int origen_y, float** biomass, float intervals, float xMin, float xMax, float yMin, float yMax, float* cost_raster, float* active_raster, float* output_raster){
    extern char is_usable;
    int exp;

    if(is_usable == 'y')
    exp = intervals * 4;
    else
    exp = intervals * 8;

    xMin = xMin - exp;
    yMin = yMin - exp;
    xMax = xMax + exp;
    yMax = yMax + exp;


    if(xMin < 0)
    xMin = 0;

    if(yMin < 0)
    yMin = 0;

    int dx[] = { -1, -1, 0, 1, 1, 1, 0,-1 };
    int dy[] = {  0,  1, 1, 1, 0, -1, -1,-1 };

    int cont = 1;

        while(!active_costs.empty()){

        cell k = *active_costs.begin();//inicio con la distancia menor
        active_costs.erase(active_costs.begin());

        if(k.x >= xMin && k.x <= xMax && k.y >= yMin && k.y <= yMax){
            cont++;
            int x, y;
            for (int i = 0; i < 8; i++){
                x = k.x + dx[i];
                y = k.y + dy[i];

                set<float>distancias;

                if(isInsideGrid(x,y,cost_raster)) {
                if(i % 2 != 0){// si es movimiento diagonal

                    if((x != origen_x || y != origen_y) && active_raster[x][y] == 0){
                        float dist=0;
                        int cont_x = k.x; int cont_y = k.y;
                        int cont_x2 = k.x; int cont_y2 = k.y;
                        int caminos = 1;

                        for(int z = 0; z < 8; z=z+2){

                            int mov_x = rutas[i][z];
                            int mov_y = rutas[i][z+1];

                            dist += (cost_raster[cont_x+mov_x][cont_y+mov_y] + cost_raster[cont_x2][cont_y2])/2;

                            if(caminos == 2 || caminos == 4){
                                //cout << dist+output_raster[k.x][k.y] << endl;
                                distancias.insert(dist+output_raster[k.x][k.y]);
                                cont_x = cont_x2 = k.x;
                                cont_y = cont_y2 = k.y;
                                caminos = 0;
                                dist = 0;
                            }else{
                                cont_x2 = cont_x+mov_x;
                                cont_y2 = cont_y+mov_y;
                                cont_x = cont_x+mov_x;
                                cont_y = cont_y+mov_y;
                            }
                            caminos++;
                        }
                        distancias.insert(1.414214 * ((cost_raster[k.x][k.y]+cost_raster[x][y])/2) + output_raster[k.x][k.y] );
                        float minimo = *distancias.begin();

                        if(minimo < output_raster[x][y] && minimo >= 0){

                            output_raster[x][y] = minimo;
                            active_costs.insert(cell(x,y,minimo));
                        }
                    }
                }
                else{

                    float dist = 0;
                    if((x != origen_x || y != origen_y) && active_raster[x][y] == 0 && isInsideGrid(x,y)){
                        dist = ((cost_raster[k.x][k.y] + cost_raster[x][y])/2) + output_raster[k.x][k.y];
                        if(dist < output_raster[x][y] && dist >= 0){

                            output_raster[x][y] = dist;
                            active_costs.insert(cell(x,y,dist));
                        }
                    }

                }
                }
            }
            active_raster[k.x][k.y] = true;
        }
    }


    active_costs.clear();
    return output_raster;
}




float* getDistance(float** biomass, float** friction, int x, int y, int rows, int cols, float intervals, float xMin, float xMax, float yMin, float yMax){

    cost_raster = new float*[rows];
    output_raster = new float*[rows];
    active_raster = new bool*[rows];

    for(int i = 0; i< rows; ++i){
        cost_raster[i] = new float[cols];
        output_raster[i] = new float[cols];
        active_raster[i] = new bool[cols];
    }

    for(int x = 0; x < ROW; x++){
        for(int y = 0; y < COL; y++){
            if(grid[x][y] == 999999)
                grid[x][y] = -9999;

            cost_raster[x][y] = friction[x][y];
            active_raster[x][y] = false;
            output_raster[x][y] = INT_MAX;
        }
    }

    active_raster[srcX][srcY] = 1;

    //se obtienen los vecinos proximos al origen y sus distancias calculadas. ordenas de menor a mayor
    set<cell> distancias = vecinos(srcX,srcY,rows,cols,cost_raster);

    output_raster =  acumulados(distancias, srcX, srcY, biomass, intervals, xMin, xMax, yMin, yMax,cost_raster,active_raster,output_raster);

    for(int r=0; r<ROW; r++){
        for(int c=0; c<COL; c++){
            if(output_raster[r][c] == INT_MAX)
                output_raster[r][c] = -9999;

        }
    }
    for(int m=0; m < rows; m++){
        delete[] cost_raster[m];
        delete[] active_raster[m];
    }
    return output_raster;
}