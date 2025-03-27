#include "Dino.h"
#include "Constants.h"

Dino::Dino() : x(50), y(SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT), velocity(0), acceleration(0.3f), jumping(false) {}

void Dino::update() {
    if (jumping) {
        y += static_cast<int>(velocity);
        velocity += acceleration;
        if (y >= SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT) {
            y = SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT;
            jumping = false;
            velocity = 0;
        }
    }
}

void Dino::jump() {
    if (!jumping) {
        jumping = true;
        velocity = -8.0f;
    }
}