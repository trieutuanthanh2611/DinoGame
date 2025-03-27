#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Texture.h"
#include "GameState.h"

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    void close();

    Texture backgroundTexture, groundTexture;
    GameState gameState;
    int state; // 0: MENU, 1: PLAYING, 2: HELP
};

#endif