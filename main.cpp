#include "Game.h"
#include <iostream>

// Hàm main để chạy trò chơi
int main(int argc, char* args[]) {
    Game game;  // Tạo đối tượng trò chơi
    if (!game.init()) {  // Khởi tạo trò chơi
        std::cout << "Failed to initialize!" << std::endl;
        return -1;  // Thoát nếu khởi tạo thất bại
    }

    game.run();  // Chạy trò chơi
    return 0;    
}