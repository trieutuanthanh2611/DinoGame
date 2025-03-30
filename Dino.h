#ifndef DINO_H
#define DINO_H

#include <SDL.h>

// Cấu trúc Dino để đại diện cho nhân vật chính
struct Dino {
    int x;              // Vị trí X của Dino
    int y;              // Vị trí Y của Dino
    float velocity;     // Tốc độ di chuyển theo chiều dọc
    float acceleration; // Gia tốc (trọng lực)
    bool jumping;       // Trạng thái nhảy

    Dino();      // Constructor để khởi tạo Dino
    void update();  // Cập nhật trạng thái của Dino
    void jump();   // Xử lý hành động nhảy
};

#endif