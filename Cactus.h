#ifndef CACTUS_H
#define CACTUS_H

#include <SDL.h>
#include "Dino.h"

// Cấu trúc Cactus để đại diện cho các chướng ngại vật trong trò chơi
struct Cactus {
    int x;      // Vị trí X của cây xương rồng
    int y;      // Vị trí Y của cây xương rồng
    int width;  // Chiều rộng của cây xương rồng
    int height; // Chiều cao của cây xương rồng

    Cactus(int posX, int size);  // Constructor để khởi tạo cây xương rồng
    void update(float speed);    // Cập nhật vị trí của cây xương rồng
    bool collidesWith(Dino& dino);  // Kiểm tra va chạm với Dino
};

#endif