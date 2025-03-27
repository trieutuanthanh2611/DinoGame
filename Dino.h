#ifndef DINO_H
#define DINO_H

#include <SDL.h>

struct Dino {
    int x;
    int y;
    float velocity;
    float acceleration;
    bool jumping;

    Dino();
    void update();
    void jump();
};

#endif