//
// Created by plutonium on 5/13/26.
//

#ifndef SANDGL_GRID_H
#define SANDGL_GRID_H

#include <cstdint>
#include <random>
#include <span>

#include "vector2D.h"

enum class CellType : uint8_t {
    Air    = 0,
    Solid  = 1,
    Sand   = 2,
    Water  = 3,
    Steam  = 4,
};




class Grid
{
public:
    Grid();
    ~Grid();
    static constexpr int gravity = 5;
    static constexpr int spreadFactor = 6;
    Dir gravityDir = {0,1};

    static constexpr int GRID_H = 100;
    static constexpr int GRID_W = 100;
    CellType grid[GRID_H][GRID_W]{CellType::Air};
    Vector2Df velocity[GRID_H][GRID_W]{{0,0}};
    bool updated [GRID_H][GRID_W]{false};

    static constexpr int DENSITY[] = {
        -2,//air
        100,//solid
        2, //sand
        1,//water
        -1//steam

    };

    void update();

private:
    std::uniform_int_distribution<int> coinDist;
    std::mt19937 rng;


    bool tryMoveCell(Vector2D pos, Dir dir);
    bool trySwitchByDensity(Vector2D pos, Dir dir);


    bool isCellEmpty(Vector2D pos) const;
    CellType getCellType( Vector2D pos) const;
    Vector2Df getVell(Vector2D);
    void setCell(Vector2D pos, CellType type);
    void setVel(Vector2D pos, Vector2Df vel);

    void updateSand(Vector2D pos);
    void updateWater(Vector2D pos);
    void updateSteam(Vector2D pos);

    bool updateParticle(Vector2D pos, std::span<Dir> directions); // my faw library span <3


    int getDensity(CellType type);

    void applyGravityVel(Vector2D pos);

};

#endif //SANDGL_GRID_H
