//
// Created by plutonium on 5/13/26.
//

#ifndef SANDGL_GRID_H
#define SANDGL_GRID_H

#include <cstdint>
#include <random>
#include "vector2D.h"


class Grid
{
public:
    Grid();
    ~Grid();
    std::mt19937 rng;


    static constexpr int GRID_H = 10;
    static constexpr int GRID_W = 10;
    unsigned int grid[GRID_H][GRID_W]{};
    unsigned int bufferGrid[GRID_H][GRID_W]{};
    void switchCells(Vector2D pos, Dir dir);
    void moveWaterUp(Vector2D pos);

    void update();

private:
    void updateSand(Vector2D pos);
    void updateWater(Vector2D pos);
    void moveCell(Vector2D pos, Dir dir);
    void pushWaterUp(Vector2D pos);
    bool isCellEmpty(Vector2D pos) const;
    unsigned int getCellID( Vector2D pos) const;

};

// ParticleType.h unused
enum class CellType : uint8_t {
    Air   = 0,
    Sand  = 1,
    Solid = 2,
    Water = 3,
};

#endif //SANDGL_GRID_H
