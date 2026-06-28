#include "Grid.h"
#include <cstdlib>
#include <iostream>
#include "vector2D.h"
#include <cstring>

Grid::Grid(): rng(std::random_device{}()), coinDist(0, 1)
{
    constexpr int startY = GRID_H * 0.7;

    for (uint16_t y = startY; y < GRID_H; ++y)
    {
        for (uint16_t x = 0; x < GRID_W; ++x)
        {
           grid[y][x] = CellType::Water;
        }}
}
Grid::~Grid()=default;



void Grid::update(){
    for (uint16_t y = 0; y < GRID_H; ++y){
        for (uint16_t x = 0; x < GRID_W; ++x){
            if (updated[y][x] == true) {continue;}
            switch (grid[y][x]) {
            case CellType::Sand:
                updateSand({x,y});
                break;
            case CellType::Water:
                updateWater({x,y});
            default:
                break;
            }
        }
    }


    memset(updated, false, sizeof(updated));
}

CellType Grid::getCellID(Vector2D pos) const
{
    // sidenote - negative numbers are converted into a biggest number possible for uint16_t
    if (pos.x >= GRID_W || pos.y >= GRID_H ) {return CellType::Solid;}
    return grid[pos.y][pos.x];
}

bool Grid::isCellEmpty(Vector2D pos) const
{
    // sidenote - negative numbers are converted into a biggest number possible for uint16_t
    if (pos.x >= GRID_W || pos.y >= GRID_H ) {return false;}
    return grid[pos.y][pos.x] == CellType::Air;
}



bool Grid::tryMoveCell(Vector2D pos, Dir dir){
    const Vector2D newPos = {
        static_cast<uint16_t>(pos.x + dir.x),
        static_cast<uint16_t>(pos.y + dir.y)};
    if (isCellEmpty(newPos))
    {
        grid[newPos.y][newPos.x] = grid[pos.y][pos.x];
        grid[pos.y][pos.x] = CellType::Air;
        updated[newPos.y][newPos.x] = true;
        return true;
    }
    return false;

}

bool Grid::tryMoveCellType(Vector2D pos, Dir dir, CellType type){
    const Vector2D newPos = {
        static_cast<uint16_t>(pos.x + dir.x),
        static_cast<uint16_t>(pos.y + dir.y)};
    if (getCellID(newPos) == type)
    {
        grid[newPos.y][newPos.x] = grid[pos.y][pos.x];
        grid[pos.y][pos.x] = type;
        updated[newPos.y][newPos.x] = true;
        return true;
    }
    return false;

}



void Grid::updateSand(Vector2D pos){
    const int8_t dirX = coinDist(rng) ? 1 : -1;
    const int8_t negDirX = -dirX;

    if (tryMoveCellType(pos, gravity, CellType::Water)) {updateWater(pos);}
    else if (tryMoveCellType(pos, {dirX, gravity.y}, CellType::Water)){updateWater(pos);}
    else if (tryMoveCellType(pos, {negDirX, gravity.y}, CellType::Water)){updateWater(pos);}


    else if (tryMoveCell(pos, gravity)) {}
    else if (tryMoveCell(pos, {dirX, gravity.y})){}
    else if (tryMoveCell(pos, {negDirX, gravity.y})){}


}


void Grid::updateWater(Vector2D pos){
    const int8_t dirX = coinDist(rng) ? 1 : -1;
    const int8_t negDirX = -dirX;

    if (tryMoveCell(pos, gravity)) {}
    else if (tryMoveCell(pos, {dirX, gravity.y})){}
    else if (tryMoveCell(pos, {negDirX, gravity.y})){}
    else if (tryMoveCell(pos, {dirX, 0})){}
    else if (tryMoveCell(pos, {negDirX, 0})){}
}


