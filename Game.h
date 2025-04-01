#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Texture.h"
#include "GameState.h"

// Lớp chính quản lý trò chơi
class Game {
public:
    Game();      // Constructor
    ~Game();     // Destructor

    bool init();  // Khởi tạo trò chơi
    void run();   // Chạy trò chơi

private:
    void close();  // Giải phóng tài nguyên

    Texture backgroundTexture;  // Texture cho nền (xóa groundTexture)
    GameState gameState;        // Trạng thái trò chơi
    int state;                  // Trạng thái hiện tại (0: MENU, 1: PLAYING, 2: HELP)
};

#endif
