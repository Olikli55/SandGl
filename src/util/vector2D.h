#ifndef SANDGL_CELLSTATE_H
#define SANDGL_CELLSTATE_H
#include <cstdint>



struct Dir
{
    int8_t x:2;
    int8_t y:2;
};//4 bits actual size = 1 byte  (with padding)

struct Vector2D
{
    uint16_t x;
    uint16_t y;
};//4 bytes = 32 bits



// structs have a padding bc of speed. if the data is correctly aligned to 4 bytes its much faster to read than unaligned data
//trade-offs:
//  i can get more space but slower reads(cpu needs to read the data 2 times)
//so that why i use the :2 in total its going to be 1 byte but thats fine.
//static_assert(sizeof(Dir2D) == 2); this pauses the program if padding is present




#endif //SANDGL_CELLSTATE_H
