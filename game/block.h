#ifndef BLOCK_H
#define BLOCK_H

#include "figure.h"

struct Block
{
    Block(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->figure = nullptr;
    }

    int x;
    int y;

    Figure* figure {nullptr};
};

#endif // BLOCK_H
