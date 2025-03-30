#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Texture.h"
#include "Dino.h"
#include "Cactus.h"
#include <SDL.h>
#include <vector>
#include <string>

// Lớp quản lý các trạng thái của trò chơi (Menu, Playing, Help)
class GameState {
public:
    GameState();  // Constructor
    void init();  // Khởi tạo tài nguyên
    void handleEvents(SDL_Event& e, bool& quit, int& gameState);  // Xử lý sự kiện
    void update(int& gameState);  // Cập nhật trạng thái
    void render(int state);  // Vẽ lên màn hình

private:
    // Trạng thái Menu
    int menuSelection;  // Lựa chọn hiện tại trong menu

    // Trạng thái Help
    std::string helpLines[3];  // Các dòng hướng dẫn
    SDL_Rect backButtonRect;   // Vùng của nút "Back"

    // Trạng thái Playing
    Texture dinoTexture, cactusTexture, scoreTexture, highScoreTexture;  // Texture cho các đối tượng
    Dino dino;  // Đối tượng Dino
    std::vector<Cactus> cactuses;  // Danh sách các cây xương rồng
    float gameSpeed;  // Tốc độ của trò chơi
    float speedIncrement;  // Tăng tốc độ
    const float MAX_SPEED_1;  // Tốc độ tối đa mức 1
    const float MAX_SPEED_2;  // Tốc độ tối đa mức 2
    const float MAX_SPEED_3;  // Tốc độ tối đa mức 3
    int lastCactusTime;  // Thời gian tạo chướng ngại vật cuối cùng
    int score;  // Điểm số hiện tại
    int highScore;  // Điểm cao nhất
    Uint32 lastScoreTime;  // Thời gian cập nhật điểm số cuối cùng
};

#endif