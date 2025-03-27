#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Texture.h"
#include "Dino.h"
#include "Cactus.h"
#include <SDL.h>
#include <vector>
#include <string>

class GameState {
public:
    GameState();
    void init();
    void handleEvents(SDL_Event& e, bool& quit, int& gameState);
    void update(int& gameState);
    void render(int state);

private:
    // Menu state
    int menuSelection;

    // Help state
    std::string helpLines[3];
    SDL_Rect backButtonRect;

    // Playing state
    Texture dinoTexture, cactusTexture, scoreTexture, highScoreTexture;
    Dino dino;
    std::vector<Cactus> cactuses;
    float gameSpeed;
    float speedIncrement;
    const float MAX_SPEED_1;
    const float MAX_SPEED_2;
    const float MAX_SPEED_3;
    int lastCactusTime;
    int score;
    int highScore;
    Uint32 lastScoreTime;
};

#endif