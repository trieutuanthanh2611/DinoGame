#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Biến toàn cục cho SDL
SDL_Window* window = nullptr;         // Cửa sổ hiển thị trò chơi
SDL_Renderer* renderer = nullptr;     // Đối tượng vẽ (renderer) cho SDL
TTF_Font* font = nullptr;            // Font chữ để hiển thị văn bản
Mix_Music* backgroundMusic = nullptr; // Nhạc nền

// Constructor cho lớp Game
Game::Game() : state(0) {}

// Destructor để giải phóng tài nguyên
Game::~Game() {
    close();  // Đóng và giải phóng tất cả tài nguyên
}

// Khởi tạo trò chơi
bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {  // Khởi tạo SDL (video và audio)
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {  // Khởi tạo SDL_image cho hình ảnh PNG
        std::cout << "IMG could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {  // Khởi tạo SDL_ttf cho văn bản
        std::cout << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {  // Khởi tạo SDL_mixer cho âm thanh
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Tạo cửa sổ và renderer
    window = SDL_CreateWindow("Dino Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Tải font và nhạc nền
    font = TTF_OpenFont("arial.ttf", 24);
    if (!font) {
        std::cout << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }

    backgroundMusic = Mix_LoadMUS("background_music.mp3");
    if (!backgroundMusic) {
        std::cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Tải texture nền và mặt đất
    if (!backgroundTexture.loadFromFile("background.png")) {
        std::cout << "Failed to load backgroundTexture!" << std::endl;
        return false;
    }
    if (!groundTexture.loadFromFile("ground.png")) {
        std::cout << "Failed to load groundTexture!" << std::endl;
        return false;
    }

    gameState.init();  // Khởi tạo trạng thái trò chơi

    return true;
}

// Giải phóng tài nguyên khi kết thúc
void Game::close() {
    Mix_FreeMusic(backgroundMusic);  // Giải phóng nhạc
    TTF_CloseFont(font);            // Đóng font
    SDL_DestroyRenderer(renderer);  // Hủy renderer
    SDL_DestroyWindow(window);      // Hủy cửa sổ
    Mix_Quit();                    // Thoát SDL_mixer
    TTF_Quit();                    // Thoát SDL_ttf
    IMG_Quit();                    // Thoát SDL_image
    SDL_Quit();                    // Thoát SDL
}

// Chạy vòng lặp chính của trò chơi
void Game::run() {
    srand(static_cast<unsigned>(time(0)));  // Khởi tạo random seed
    Mix_PlayMusic(backgroundMusic, -1);     // Phát nhạc nền lặp lại

    bool quit = false;  // Biến để kiểm tra thoát trò chơi
    SDL_Event e;        // Sự kiện SDL

    while (!quit) {  // Vòng lặp chính
        while (SDL_PollEvent(&e) != 0) {  // Xử lý sự kiện
            gameState.handleEvents(e, quit, state);  // Xử lý sự kiện trong trạng thái trò chơi
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Xóa màn hình (màu trắng)
        SDL_RenderClear(renderer);

        // Vẽ nền và mặt đất
        backgroundTexture.render(0, 0, nullptr, SCREEN_WIDTH, SCREEN_HEIGHT);
        groundTexture.render(0, SCREEN_HEIGHT - GROUND_HEIGHT, nullptr, SCREEN_WIDTH, GROUND_HEIGHT);

        gameState.update(state);  // Cập nhật trạng thái trò chơi
        gameState.render(state);  // Vẽ trạng thái trò chơi

        SDL_RenderPresent(renderer);  // Hiển thị lên màn hình
        SDL_Delay(16);  // Giới hạn FPS (khoảng 60 FPS)
    }
}