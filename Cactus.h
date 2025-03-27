#ifndef CACTUS_H
#define CACTUS_H

#include <SDL.h>
#include "Dino.h"

struct Cactus {
    int x;
    int y;
    int width;
    int height;

    Cactus(int posX, int size);
    void update(float speed);
    bool collidesWith(Dino& dino);
};

#endif