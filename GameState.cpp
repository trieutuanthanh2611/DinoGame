#include "GameState.h"
#include "Constants.h"
#include <cstdlib>
#include <iostream>

// Constructor cho lớp GameState, khởi tạo các giá trị ban đầu
GameState::GameState() : menuSelection(0), gameSpeed(5.0f), speedIncrement(0.001f),
                        MAX_SPEED_1(5.0f), MAX_SPEED_2(7.0f), MAX_SPEED_3(9.0f),
                        lastCactusTime(0), score(0), highScore(0), lastScoreTime(0) {
    // menuSelection: Lựa chọn trong menu (0: Play, 1: Help, 2: Exit)
    // gameSpeed: Tốc độ di chuyển của chướng ngại vật
    // speedIncrement: Tăng tốc độ theo thời gian
    // MAX_SPEED_*: Các mức tốc độ tối đa
    // lastCactusTime: Thời gian tạo chướng ngại vật cuối cùng
    // score: Điểm số hiện tại
    // highScore: Điểm cao nhất
    // lastScoreTime: Thời gian cập nhật điểm số cuối cùng

    helpLines[0] = "1. Press the space key to jump.";  // Hướng dẫn 1: Nhấn phím cách để nhảy
    helpLines[1] = "2. Avoid obstacles; the longer you survive, the higher your score.";  // Hướng dẫn 2: Tránh chướng ngại, sống càng lâu điểm càng cao
    helpLines[2] = "3. The game will speed up over time.";  // Hướng dẫn 3: Trò chơi sẽ tăng tốc theo thời gian

    backButtonRect = {10, SCREEN_HEIGHT - 30 - 24, 50, 24};  // Vị trí và kích thước nút "Back" trong màn hình Help
}

// Khởi tạo tài nguyên (texture) cho trò chơi
void GameState::init() {
    if (!dinoTexture.loadFromFile("dino.png")) {  // Tải texture cho Dino
        std::cout << "Failed to load dinoTexture!" << std::endl;
    }
    if (!cactusTexture.loadFromFile("cactus.png")) {  // Tải texture cho Cactus
        std::cout << "Failed to load cactusTexture!" << std::endl;
    }
}

// Xử lý các sự kiện từ người dùng
void GameState::handleEvents(SDL_Event& e, bool& quit, int& gameState) {
    if (e.type == SDL_QUIT) quit = true;  // Thoát nếu người dùng đóng cửa sổ

    if (gameState == 0) {  // Trạng thái Menu
        if (e.type == SDL_KEYDOWN) {  // Xử lý phím nhấn
            if (e.key.keysym.sym == SDLK_UP) {  // Phím lên để di chuyển lên trong menu
                menuSelection = (menuSelection - 1 + 3) % 3;  // Chuyển lên lựa chọn trước
            }
            if (e.key.keysym.sym == SDLK_DOWN) {  // Phím xuống để di chuyển xuống trong menu
                menuSelection = (menuSelection + 1) % 3;  // Chuyển xuống lựa chọn sau
            }
            if (e.key.keysym.sym == SDLK_RETURN) {  // Phím Enter để chọn
                if (menuSelection == 0) gameState = 1;  // Chọn Play
                else if (menuSelection == 1) gameState = 2;  // Chọn Help
                else if (menuSelection == 2) quit = true;  // Chọn Exit
            }
        }
    }
    else if (gameState == 1) {  // Trạng thái Playing
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {  // Nhấn phím cách để nhảy
            dino.jump();
        }
    }
    else if (gameState == 2) {  // Trạng thái Help
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {  // Nhấn Esc để quay lại Menu
            gameState = 0;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {  // Nhấn chuột vào nút Back
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);  // Lấy vị trí chuột
            if (mouseX >= backButtonRect.x && mouseX <= backButtonRect.x + backButtonRect.w &&
                mouseY >= backButtonRect.y && mouseY <= backButtonRect.y + backButtonRect.h) {
                gameState = 0;  // Quay lại Menu
            }
        }
    }
}

// Cập nhật trạng thái trò chơi
void GameState::update(int& gameState) {
    if (gameState == 1) {  // Trạng thái Playing
        dino.update();  // Cập nhật vị trí của Dino

        // Tăng tốc độ theo thời gian và điểm số
        speedIncrement = 0.001f + (score / 1000.0f) * 0.01f;

        if (score < 100) {  // Tăng tốc độ đến mức 1
            if (gameSpeed < MAX_SPEED_1) gameSpeed += speedIncrement;
        }
        else if (score < 200) {  // Tăng tốc độ đến mức 2
            if (gameSpeed < MAX_SPEED_2) gameSpeed += speedIncrement;
        }
        else {  // Tăng tốc độ đến mức 3
            if (gameSpeed < MAX_SPEED_3) gameSpeed += speedIncrement;
        }

        // Cập nhật điểm số mỗi 100ms
        if (SDL_GetTicks() - lastScoreTime >= 100) {
            score++;
            lastScoreTime = SDL_GetTicks();
        }

        // Tạo chướng ngại vật mới sau mỗi 1500ms
        if (SDL_GetTicks() - lastCactusTime > 1500) {
            int numCactuses = rand() % 3 + 1;  // Số lượng cây xương rồng ngẫu nhiên (1-3)
            int lastX = SCREEN_WIDTH;  // Vị trí bắt đầu từ cạnh phải màn hình
            for (int i = 0; i < numCactuses; i++) {
                int size = rand() % 3;  // Kích thước ngẫu nhiên (0, 1, 2)
                cactuses.push_back(Cactus(lastX, size));  // Thêm cây xương rồng mới
                lastX += cactuses.back().width + 5;  // Cập nhật vị trí cho cây tiếp theo
            }
            lastCactusTime = SDL_GetTicks();  // Cập nhật thời gian tạo chướng ngại vật
        }

        // Cập nhật và kiểm tra va chạm với các cây xương rồng
        for (auto it = cactuses.begin(); it != cactuses.end();) {
            it->update(gameSpeed);  // Di chuyển cây xương rồng
            if (it->collidesWith(dino)) {  // Nếu va chạm
                if (score > highScore) highScore = score;  // Cập nhật điểm cao nhất
                gameState = 0;  // Quay lại Menu
                cactuses.clear();  // Xóa tất cả chướng ngại vật
                score = 0;  // Đặt lại điểm số
                gameSpeed = 5.0f;  // Đặt lại tốc độ ban đầu
                speedIncrement = 0.001f;  // Đặt lại tăng tốc
                break;
            }
            if (it->x + it->width < 0) {  // Nếu cây xương rồng ra khỏi màn hình
                it = cactuses.erase(it);  // Xóa cây đó
            }
            else {
                ++it;  // Tiếp tục với cây tiếp theo
            }
        }
    }
}

// Vẽ các thành phần lên màn hình
void GameState::render(int state) {
    if (state == 0) {  // Trạng thái Menu
        SDL_Color textColor = { 255, 255, 255 };  // Màu trắng cho văn bản
        SDL_Color selectedColor = { 255, 0, 0 };  // Màu đỏ cho lựa chọn hiện tại
        Texture playText, helpText, exitText;

        // Tạo và vẽ các lựa chọn trong menu
        playText.loadFromText("Play", menuSelection == 0 ? selectedColor : textColor);
        helpText.loadFromText("Help", menuSelection == 1 ? selectedColor : textColor);
        exitText.loadFromText("Exit", menuSelection == 2 ? selectedColor : textColor);

        playText.render(SCREEN_WIDTH / 2 - playText.getWidth() / 2, SCREEN_HEIGHT / 2 - 60);  // Vẽ "Play"
        helpText.render(SCREEN_WIDTH / 2 - helpText.getWidth() / 2, SCREEN_HEIGHT / 2 - 20);  // Vẽ "Help"
        exitText.render(SCREEN_WIDTH / 2 - exitText.getWidth() / 2, SCREEN_HEIGHT / 2 + 20);  // Vẽ "Exit"
    }
    else if (state == 2) {  // Trạng thái Help
        SDL_Color textColor = { 255, 255, 255 };  // Màu trắng cho văn bản
        int lineHeight = 30;  // Khoảng cách giữa các dòng
        int totalHeight = lineHeight * 3;  // Tổng chiều cao của các dòng hướng dẫn
        int startY = (SCREEN_HEIGHT - totalHeight) / 2;  // Vị trí bắt đầu vẽ

        // Vẽ các dòng hướng dẫn
        for (int i = 0; i < 3; i++) {
            Texture helpText;
            helpText.loadFromText(helpLines[i], textColor);
            helpText.render(10, startY + i * lineHeight);  // Vẽ từng dòng
        }

        // Vẽ nút "Back"
        Texture backButtonTexture;
        backButtonTexture.loadFromText("Back", textColor);
        backButtonRect.w = backButtonTexture.getWidth();  // Cập nhật chiều rộng nút
        backButtonRect.h = backButtonTexture.getHeight();  // Cập nhật chiều cao nút
        backButtonRect.y = SCREEN_HEIGHT - 30 - backButtonRect.h;  // Đặt vị trí Y
        backButtonTexture.render(backButtonRect.x, backButtonRect.y);  // Vẽ nút
    }
    else if (state == 1) {  // Trạng thái Playing
        dinoTexture.render(dino.x, dino.y, nullptr, DINO_WIDTH, DINO_HEIGHT);  // Vẽ Dino

        SDL_Color textColor = { 255, 255, 255 };  // Màu trắng cho văn bản
        scoreTexture.loadFromText("Score: " + std::to_string(score), textColor);  // Tạo văn bản điểm số
        highScoreTexture.loadFromText("High Score: " + std::to_string(highScore), textColor);  // Tạo văn bản điểm cao nhất
        scoreTexture.render(10, 10);  // Vẽ điểm số
        highScoreTexture.render(10, 40);  // Vẽ điểm cao nhất

        // Vẽ tất cả các cây xương rồng
        for (const auto& cactus : cactuses) {
            cactusTexture.render(cactus.x, cactus.y, nullptr, cactus.width, cactus.height);
        }
    }
}