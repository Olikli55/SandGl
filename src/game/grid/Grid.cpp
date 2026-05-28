#include "Grid.h"
#include <cstdlib>
#include <iostream>
Grid::Grid()=default;

Grid::~Grid()=default;



void Grid::update(){



    for (int y = 0; y < GRID_H; ++y){
        for (int x = 0; x < GRID_W; ++x){
            bufferGrid[y][x] = (x+y) % 4;
            if (x == 0 || y == 0)
            {
                bufferGrid[y][x] = 1;
            }

            switch (grid[y][x]){

            case 1:
                break;
                updateSand(x,y);
                break;
            }
        }
    }
    grid[GRID_H-1][GRID_W /2-1] = 0;

    std::memcpy(grid , bufferGrid, sizeof(grid));

}

unsigned int Grid::getCellID(int x,  int y) const
{
    if (x >= GRID_W || x < 0 || y >= GRID_H || y < 0) {return 6;}
    return bufferGrid[y][x];

}

bool Grid::isCellEmpty(int x, int y)
{
    if (x >= GRID_W || x < 0 || y >= GRID_H || y < 0) {return false;}
    return bufferGrid[y][x] == 0;
}

void Grid::updateSand(int x, int y){
    const int dirY = y - 1;
    if (isCellEmpty(x,dirY))
    {
        bufferGrid[dirY][x] = 1; //sand
        bufferGrid[y][x] = 0; //air
        return;
    }
    const int dirX = x +((std::rand() % 2 == 0) ? -1 : 1);
    if (isCellEmpty(dirX,dirY))
    {

        bufferGrid[dirY][dirX] = 1; //sand
        bufferGrid[y][x] = 0; //air
        return;
    }
    if (isCellEmpty(-dirX, dirY))
    {
        bufferGrid[-dirY][dirX] = 1; //sand
        bufferGrid[y][x] = 0; //air
        return;
    }

}
