//
// Created by plutonium on 5/13/26.
//

#ifndef SANDGL_GRID_H
#define SANDGL_GRID_H
#include "cellState.h"
#include <cstring>
#include <cstdint>


class Grid
{
public:
    Grid();
    ~Grid();


    static constexpr int GRID_H = 200;
    static constexpr int GRID_W = 200;
    unsigned int grid[GRID_H][GRID_W]{};
    unsigned int bufferGrid[GRID_H][GRID_W]{};

    void update();
    void init();
    void updateSand(int x, int y);
private:
    bool isCellEmpty(int x, int y);
    unsigned int getCellID( int x,  int y) const;

};

// ParticleType.h
enum class CellType : uint8_t {
    Air   = 0,
    Sand  = 1,
    Solid = 2,
    Water = 3,
};

#endif //SANDGL_GRID_H
