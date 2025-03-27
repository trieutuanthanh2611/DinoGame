#include "GameState.h"
#include "Constants.h"
#include <cstdlib>
#include <iostream>
GameState::GameState() : menuSelection(0), gameSpeed(5.0f), speedIncrement(0.001f),
                        MAX_SPEED_1(5.0f), MAX_SPEED_2(7.0f), MAX_SPEED_3(9.0f),
                        lastCactusTime(0), score(0), highScore(0), lastScoreTime(0) {
    helpLines[0] = "1. Press the space key to jump.";
    helpLines[1] = "2. Avoid obstacles; the longer you survive, the higher your score.";
    helpLines[2] = "3. The game will speed up over time.";

    backButtonRect = {10, SCREEN_HEIGHT - 30 - 24, 50, 24}; // Kích thước mặc định
}

void GameState::init() {
    if (!dinoTexture.loadFromFile("dino.png")) {
        std::cout << "Failed to load dinoTexture!" << std::endl;
    }
    if (!cactusTexture.loadFromFile("cactus.png")) {
        std::cout << "Failed to load cactusTexture!" << std::endl;
    }
}

void GameState::handleEvents(SDL_Event& e, bool& quit, int& gameState) {
    if (e.type == SDL_QUIT) quit = true;

    if (gameState == 0) { // Menu
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_UP) {
                menuSelection = (menuSelection - 1 + 3) % 3;
            }
            if (e.key.keysym.sym == SDLK_DOWN) {
                menuSelection = (menuSelection + 1) % 3;
            }
            if (e.key.keysym.sym == SDLK_RETURN) {
                if (menuSelection == 0) gameState = 1; // Playing
                else if (menuSelection == 1) gameState = 2; // Help
                else if (menuSelection == 2) quit = true;
            }
        }
    }
    else if (gameState == 1) { // Playing
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
            dino.jump();
        }
    }
    else if (gameState == 2) { // Help
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            gameState = 0; // Menu
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX >= backButtonRect.x && mouseX <= backButtonRect.x + backButtonRect.w &&
                mouseY >= backButtonRect.y && mouseY <= backButtonRect.y + backButtonRect.h) {
                gameState = 0; // Menu
            }
        }
    }
}

void GameState::update(int& gameState) {
    if (gameState == 1) { // Playing
        dino.update();

        speedIncrement = 0.001f + (score / 1000.0f) * 0.01f;

        if (score < 100) {
            if (gameSpeed < MAX_SPEED_1) gameSpeed += speedIncrement;
        }
        else if (score < 200) {
            if (gameSpeed < MAX_SPEED_2) gameSpeed += speedIncrement;
        }
        else {
            if (gameSpeed < MAX_SPEED_3) gameSpeed += speedIncrement;
        }

        if (SDL_GetTicks() - lastScoreTime >= 100) {
            score++;
            lastScoreTime = SDL_GetTicks();
        }

        if (SDL_GetTicks() - lastCactusTime > 1500) {
            int numCactuses = rand() % 3 + 1;
            int lastX = SCREEN_WIDTH;
            for (int i = 0; i < numCactuses; i++) {
                int size = rand() % 3;
                cactuses.push_back(Cactus(lastX, size));
                lastX += cactuses.back().width + 5;
            }
            lastCactusTime = SDL_GetTicks();
        }

        for (auto it = cactuses.begin(); it != cactuses.end();) {
            it->update(gameSpeed);
            if (it->collidesWith(dino)) {
                if (score > highScore) highScore = score;
                gameState = 0; // Menu
                cactuses.clear();
                score = 0;
                gameSpeed = 5.0f;
                speedIncrement = 0.001f;
                break;
            }
            if (it->x + it->width < 0) {
                it = cactuses.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

void GameState::render(int state) {
    if (state == 0) { // Menu
        SDL_Color textColor = { 255, 255, 255 };
        SDL_Color selectedColor = { 255, 0, 0 };
        Texture playText, helpText, exitText;

        playText.loadFromText("Play", menuSelection == 0 ? selectedColor : textColor);
        helpText.loadFromText("Help", menuSelection == 1 ? selectedColor : textColor);
        exitText.loadFromText("Exit", menuSelection == 2 ? selectedColor : textColor);

        playText.render(SCREEN_WIDTH / 2 - playText.getWidth() / 2, SCREEN_HEIGHT / 2 - 60);
        helpText.render(SCREEN_WIDTH / 2 - helpText.getWidth() / 2, SCREEN_HEIGHT / 2 - 20);
        exitText.render(SCREEN_WIDTH / 2 - exitText.getWidth() / 2, SCREEN_HEIGHT / 2 + 20);
    }
    else if (state == 2) { // Help
        SDL_Color textColor = { 255, 255, 255 };
        int lineHeight = 30;
        int totalHeight = lineHeight * 3;
        int startY = (SCREEN_HEIGHT - totalHeight) / 2;

        for (int i = 0; i < 3; i++) {
            Texture helpText;
            helpText.loadFromText(helpLines[i], textColor);
            helpText.render(10, startY + i * lineHeight);
        }

        Texture backButtonTexture;
        backButtonTexture.loadFromText("Back", textColor);
        backButtonRect.w = backButtonTexture.getWidth();
        backButtonRect.h = backButtonTexture.getHeight();
        backButtonRect.y = SCREEN_HEIGHT - 30 - backButtonRect.h;
        backButtonTexture.render(backButtonRect.x, backButtonRect.y);
    }
    else if (state == 1) { // Playing
        dinoTexture.render(dino.x, dino.y, nullptr, DINO_WIDTH, DINO_HEIGHT);

        SDL_Color textColor = { 255, 255, 255 };
        scoreTexture.loadFromText("Score: " + std::to_string(score), textColor);
        highScoreTexture.loadFromText("High Score: " + std::to_string(highScore), textColor);
        scoreTexture.render(10, 10);
        highScoreTexture.render(10, 40);

        for (const auto& cactus : cactuses) {
            cactusTexture.render(cactus.x, cactus.y, nullptr, cactus.width, cactus.height);
        }
    }
}
