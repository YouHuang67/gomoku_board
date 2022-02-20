#ifndef ZOBRIST_KEY_H__
#define ZOBRIST_KEY_H__

#include <cstdlib>
#include "utils.h"


inline Uint64 Rand64()
{
    return (static_cast<Uint64>(std::rand()) <<  0) ^ 
           (static_cast<Uint64>(std::rand()) << 15) ^ 
           (static_cast<Uint64>(std::rand()) << 30) ^ 
           (static_cast<Uint64>(std::rand()) << 45) ^ 
           (static_cast<Uint64>(std::rand()) << 60);
}


inline Uint64*** GetZobristKeys()
{
    std::srand(42);
    Uint64*** ptr = new Uint64**[3];
    for (int i = 0; i < 3; i++)
    {
        ptr[i] = new Uint64*[SIZE];
        for (int j = 0; j < SIZE; j++)
        {
            ptr[i][j] = new Uint64[SIZE];
            for (int k = 0; k < SIZE; k++)
                ptr[i][j][k] = Rand64();
        }
    }
    return ptr;
}

#endif