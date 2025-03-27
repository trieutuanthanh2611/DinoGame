#include "Game.h"
#include "Constants.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
Mix_Music* backgroundMusic = nullptr;

Game::Game() : state(0) {}

Game::~Game() {
    close();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "IMG could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {
        std::cout << "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

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

    if (!backgroundTexture.loadFromFile("background.png")) {
        std::cout << "Failed to load backgroundTexture!" << std::endl;
        return false;
    }
    if (!groundTexture.loadFromFile("ground.png")) {
        std::cout << "Failed to load groundTexture!" << std::endl;
        return false;
    }

    gameState.init();

    return true;
}

void Game::close() {
    Mix_FreeMusic(backgroundMusic);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::run() {
    srand(static_cast<unsigned>(time(0)));
    Mix_PlayMusic(backgroundMusic, -1);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            gameState.handleEvents(e, quit, state);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        backgroundTexture.render(0, 0, nullptr, SCREEN_WIDTH, SCREEN_HEIGHT);
        groundTexture.render(0, SCREEN_HEIGHT - GROUND_HEIGHT, nullptr, SCREEN_WIDTH, GROUND_HEIGHT);

        gameState.update(state);
        gameState.render(state);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}