#include "Grid.h"
#include <cstdlib>
#include <iostream>
#include "vector2D.h"
#include <cstring>
#include <algorithm>

Grid::Grid(): coinDist(0, 1), rng(std::random_device{}())
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
    const bool reverseOrder = (coinDist(rng) != 0);


    for (uint16_t y = GRID_H; y-- > 0;){
        for (uint16_t _x = GRID_W; _x-- > 0; ){
            
            const uint16_t x = reverseOrder ? (GRID_W -1 - _x) : _x;
            if (updated[y][x] == true) {continue;}
            switch (grid[y][x])
            {
            case CellType::Sand:
               updateSand({x,y});
                break;
            case CellType::Water:
                updateWater({x,y});
                break;
            case CellType::Steam:
                updateSteam({x,y});
                break;
            default:
                break;
            }
        }
    }


    memset(updated, false, sizeof(updated));
}


void Grid::setCell(Vector2D pos, CellType type)
{
    grid[pos.y][pos.x] = type;
}

void Grid::setVel(Vector2D pos, Vector2Df vel)
{
    velocity[pos.y][pos.x] = vel;
}

CellType Grid::getCellType(Vector2D pos) const
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


bool Grid::trySwitchByDensity(Vector2D pos, Dir dir){
    const Vector2D newPos = {
        static_cast<uint16_t>(pos.x + dir.x),
        static_cast<uint16_t>(pos.y + dir.y)};
    const CellType tempCellType = getCellType(newPos);

    if (getCellType(pos) == CellType::Steam && getCellType(newPos) != CellType::Steam ){std::cout << getDensity(getCellType(newPos)) << ' ' << getDensity(getCellType(pos)) << '\n';}
    if (getDensity(getCellType(newPos)) >= getDensity(getCellType(pos))){return false;}
    if ( getCellType(pos) == CellType::Steam && getCellType(newPos) != CellType::Steam){std::cout << " yep its smaller lets move!" << '\n';}

    grid[newPos.y][newPos.x] = grid[pos.y][pos.x];
    grid[pos.y][pos.x] = tempCellType;
    updated[newPos.y][newPos.x] = true;

    return true;

}



void Grid::updateSand(Vector2D pos){
    const int8_t dirX = coinDist(rng) ? 1 : -1;
    const int8_t negDirX = -dirX;
    Dir directions[3] = {
        Dir{0, gravityDir.y},
        Dir{dirX, gravityDir.y},
        Dir{negDirX, gravityDir.y}
    };
    updateParticle(pos, directions);



}


void Grid::updateWater(Vector2D pos)
{
    const int8_t dirX = coinDist(rng) ? 1 : -1;
    const int8_t negDirX = -dirX;

    Dir directions[5] = {
        Dir{0, gravityDir.y},
        Dir{dirX, gravityDir.y},
        Dir{negDirX, gravityDir.y},
        Dir{dirX, 0},
        Dir{negDirX, 0},
    };

    updateParticle(pos, directions);
}

void Grid::updateSteam(Vector2D pos)
{
    const int8_t dirX = coinDist(rng) ? 1 : -1;
    const int8_t negDirX = -dirX;
    const int8_t negGravY = -gravityDir.y;
    Dir directions[]= {
        Dir{0, negGravY},
        Dir{dirX, negGravY},
        Dir{negDirX, negGravY},
        Dir{dirX, 0},
        Dir{negDirX, 0}};

    updateParticle(pos, directions);
 }


bool Grid::updateParticle(Vector2D pos, std::span<Dir> directions)
{
    return std::ranges::any_of(directions, [this, pos](const Dir dir)
    {
        return trySwitchByDensity(pos, dir);
    });
}

int Grid::getDensity(CellType type){
    return DENSITY[static_cast<int>(type)];
}

void Grid::applyGravityVel(Vector2D pos)
{
    CellType type = getCellType(pos);
    if (type == CellType::Air || type == CellType::Solid){return;}


}
