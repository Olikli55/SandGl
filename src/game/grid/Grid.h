//
// Created by plutonium on 5/13/26.
//

#ifndef SANDGL_GRID_H
#define SANDGL_GRID_H

#include <cstdint>
#include <random>

#include "vector2D.h"

enum class CellType : uint8_t {
    Air    = 0,
    Solid  = 1,
    Sand   = 2,
    Water  = 3,
    Gas    = 4,
};




class Grid
{
public:
    Grid();
    ~Grid();
    Dir gravity = {0,1};

    static constexpr int GRID_H = 100;
    static constexpr int GRID_W = 100;
    CellType grid[GRID_H][GRID_W]{CellType::Air};
    bool updated [GRID_H][GRID_W]{false};


    void update();

private:
    std::uniform_int_distribution<int> coinDist;
    std::mt19937 rng;


    bool tryMoveCell(Vector2D pos, Dir dir);
    bool tryMoveCellType(Vector2D pos, Dir dir, CellType type);


    bool isCellEmpty(Vector2D pos) const;
    CellType getCellID( Vector2D pos) const;

    void updateSand(Vector2D pos);
    void updateWater(Vector2D pos);


};

#endif //SANDGL_GRID_H
