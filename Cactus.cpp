#include "Cactus.h"
#include "Constants.h"

Cactus::Cactus(int posX, int size) {
    x = posX;
    width = size == 0 ? 20 : (size == 1 ? 30 : 40);
    height = width * 1.5;
    y = SCREEN_HEIGHT - GROUND_HEIGHT - height;
}

void Cactus::update(float speed) {
    x -= static_cast<int>(speed);
}

bool Cactus::collidesWith(Dino& dino) {
    SDL_Rect dinoRect = { dino.x, dino.y, DINO_WIDTH, DINO_HEIGHT };
    SDL_Rect cactusRect = { x, y, width, height };
    return SDL_HasIntersection(&dinoRect, &cactusRect);
}