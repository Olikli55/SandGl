#include "Grid.h"
#include <cstdlib>
#include <iostream>
#include "vector2D.h"
#include <cstring>

Grid::Grid(): rng(std::random_device{}())
{
    constexpr int startY = GRID_H * 0.7;

    for (int y = startY; y < GRID_H; ++y)
    {
        for (int x = 0; x < GRID_W; ++x)
        {
        bufferGrid[y][x] = 2;
        }}
    return;

    for (int y = 0; y < GRID_H; ++y)
    {
        for (int x = 0; x < GRID_W; ++x)
        {
            bufferGrid[y][x] = ((x + y) % 2 == 0) ? 10 : 0;

        }
    }
   // constexpr int startY = GRID_H * 0.7;

    for (int y = startY; y < GRID_H; ++y)
    {
        for (int x = 0; x < GRID_W; ++x)
        {
            if (x % 2 == 0){
                bufferGrid[y][x] = 10;
            }else
            {
                bufferGrid[y][x] = 0;
            }

        }
    }
    std::memcpy(grid, bufferGrid, sizeof(grid));
}
Grid::~Grid()=default;



void Grid::update(){
    //grid[0][GRID_H/3] = 1;
    // grid[0][GRID_H/2-2] = 1;
    //grid[0][GRID_H/2] = 1;
    //grid[0][GRID_H/2-4] = 1;
    //grid[0][GRID_H/2-10] = 1;
    //grid[0][GRID_H/2-6] = 1;
    for (uint16_t y = 0; y < GRID_H; ++y){
        for (uint16_t x = 0; x < GRID_W; ++x){

            switch (grid[y][x]){

            case 1:
                updateSand({x,y});
                break;
            case 2:
                updateWater({x,y});
                break;
            default:
                break;
            }
        }
    }

    std::memcpy(grid , bufferGrid, sizeof(grid));

}

unsigned int Grid::getCellID(Vector2D pos) const
{
    //@todo if he Vector2D is only a unsigned value there is no need to chek for zero
    // sidenote - negative numbers are converted into a biggest number possible for uint16_t
    if (pos.x >= GRID_W || pos.x < 0 || pos.y >= GRID_H || pos.y < 0) {return 6;}
    return bufferGrid[pos.y][pos.x];

}

bool Grid::isCellEmpty(Vector2D pos) const
{
    if (pos.x >= GRID_W || pos.x < 0 || pos.y >= GRID_H || pos.y < 0) {return false;}
    return bufferGrid[pos.y][pos.x] == 0;
}

void Grid::moveCell(Vector2D pos, Dir dir)
{

}

void Grid::pushWaterUp(Vector2D pos)
{

}

void Grid::updateSand(Vector2D pos){
    const uint16_t dirY = pos.y + 1;
    if (const unsigned short id = getCellID({pos.x,dirY});
        id == 0 || id == 2){
        bufferGrid[dirY][pos.x] = grid[pos.y][pos.x];

    }else
    {
        std::uniform_int_distribution<int> coin(0, 1);

        // i dont need to chek if the value is negative bc static  cast converts negative value to the max value and that is automaticly out of bounds
        if (const int8_t dx = coin(rng) ? 1 : -1;
            isCellEmpty({static_cast<uint16_t>(pos.x + dx),dirY})){

            bufferGrid[dirY][pos.x + dx] = grid[pos.y][pos.x];
            bufferGrid[pos.y][pos.x] = grid[dirY][pos.x+dx];

        } else if (isCellEmpty({static_cast<uint8_t>(pos.x - dx), dirY})){

            bufferGrid[dirY][pos.x - dx] = grid[pos.y][pos.x];
            bufferGrid[pos.y][pos.x] = grid[dirY][pos.x-dx];
        }
    }
}

void Grid::updateWater(Vector2D pos)
{
    const uint16_t dirY = pos.y + 1;
    if (isCellEmpty({pos.x, dirY}))
    {
        bufferGrid[dirY][pos.x] = grid[pos.y][pos.x];
        bufferGrid[pos.y][pos.x] = grid[dirY][pos.x];
        return;
    }
    std::uniform_int_distribution<int> coin(0, 1);

    const int16_t dx = coin(rng) ? 1 : -1;
    if (isCellEmpty({static_cast<uint16_t>(pos.x + dx),dirY}))
    {
        bufferGrid[dirY][pos.x + dx] = grid[pos.y][pos.x];
        bufferGrid[pos.y][pos.x] = grid[dirY][pos.x + dx];
        return;
    }
    if (isCellEmpty({static_cast<uint16_t>(pos.x - dx), dirY}))
    {
        bufferGrid[dirY][pos.x - dx] = grid[pos.y][pos.x];
        bufferGrid[pos.y][pos.x] = grid[dirY][pos.x - dx];
        return;
    }

    if (isCellEmpty({static_cast<uint16_t>(pos.x + dx), pos.y}))
    {
        bufferGrid[pos.y][pos.x + dx] = 2;
        bufferGrid[pos.y][pos.x] = 0;
        return;
    }
    if (isCellEmpty({static_cast<uint16_t>(pos.x - dx), pos.y}))
    {
        bufferGrid[pos.y][pos.x - dx] = 2;
        bufferGrid[pos.y][pos.x] = 0;
        return;
    }
}
