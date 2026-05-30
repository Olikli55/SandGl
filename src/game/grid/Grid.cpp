#include "Grid.h"
#include <cstdlib>
#include <iostream>
#include "cellState.h"
#include <cstring>

Grid::Grid(): rng(std::random_device{}())
{
    for (int y = 0; y < GRID_H; ++y)
    {
        for (int x = 0; x < GRID_W; ++x)
        {
            bufferGrid[y][x] = ((x + y) % 2 == 0) ? 2 : 0;

        }
    }
    constexpr int startY = GRID_H * 0.7;   // half down
    constexpr int lineSpacing = 2;       // every 2 columns => x = 0,2,4,... (change as desired)


    for (int y = startY; y < GRID_H; ++y)
    {
        for (int x = 0; x < GRID_W; ++x)
        {
            if (x % lineSpacing == 0){
                bufferGrid[y][x] = 2u;
            }else
            {
                bufferGrid[y][x] = 0u;
            }

        }
    }
    std::memcpy(grid, bufferGrid, sizeof(grid));
}
Grid::~Grid()=default;



void Grid::update(){
    // grid[0][GRID_H/2-1] = 1;
    // grid[0][GRID_H/2-2] = 1;
     grid[0][GRID_H/2-3] = 1;
    // grid[0][GRID_H/2-4] = 1;
    // grid[0][GRID_H/2-5] = 1;
    // grid[0][GRID_H/2-6] = 1;
    std::memcpy(bufferGrid, grid, sizeof(grid));
    for (int y = 0; y < GRID_H; ++y){
        for (int x = 0; x < GRID_W; ++x){

            switch (grid[y][x]){

            case 1:
                updateSand(x,y);
                break;
            }
        }
    }

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
    const int dirY = y + 1;
    if (isCellEmpty(x,dirY))
    {
        bufferGrid[dirY][x] = 1; //sand
        bufferGrid[y][x] = 0; //air
        return;
    }
    std::uniform_int_distribution<int> coin(0, 1);

    const int dx = coin(rng) ? 1 : -1;
    if (isCellEmpty(x + dx,dirY))
    {

        bufferGrid[dirY][x + dx] = 1; //sand
        bufferGrid[y][x] = 0; //air
        return;
    }
    if (isCellEmpty(x - dx, dirY))
    {
        bufferGrid[dirY][x - dx] = 1; //sand
        bufferGrid[y][x] = 0; //air
        return;
    }

}
