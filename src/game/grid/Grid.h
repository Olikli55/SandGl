//
// Created by plutonium on 5/13/26.
//

#ifndef SANDGL_GRID_H
#define SANDGL_GRID_H

#include <cstdint>
#include <random>



class Grid
{
public:
    Grid();
    ~Grid();
    std::mt19937 rng;


    static constexpr int GRID_H = 1000;
    static constexpr int GRID_W = 1000;
    unsigned int grid[GRID_H][GRID_W]{};
    unsigned int bufferGrid[GRID_H][GRID_W]{};

    void update();
    void init();
    void updateSand(int x, int y);
private:
    bool isCellEmpty(int x, int y);
    unsigned int getCellID( int x,  int y) const;

};

// ParticleType.h unused
enum class CellType : uint8_t {
    Air   = 0,
    Sand  = 1,
    Solid = 2,
    Water = 3,
};

#endif //SANDGL_GRID_H
