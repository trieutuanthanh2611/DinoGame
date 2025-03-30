#include "Cactus.h"
#include "Constants.h"

// Constructor cho đối tượng Cactus, khởi tạo vị trí và kích thước
Cactus::Cactus(int posX, int size) {
    x = posX;  // Vị trí X của cây xương rồng trên màn hình
    width = size == 0 ? 20 : (size == 1 ? 30 : 40);  // Chiều rộng tùy thuộc vào kích thước (0: nhỏ, 1: trung bình, 2: lớn)
    height = width * 1.5;  // Chiều cao tỉ lệ với chiều rộng
    y = SCREEN_HEIGHT - GROUND_HEIGHT - height;  // Vị trí Y cố định trên mặt đất
}

// Cập nhật vị trí của cây xương rồng khi di chuyển (giảm X để tạo hiệu ứng chạy sang trái)
void Cactus::update(float speed) {
    x -= static_cast<int>(speed);  // Di chuyển cây xương rồng sang trái với tốc độ cho trước
}

// Kiểm tra va chạm giữa cây xương rồng và Dino
bool Cactus::collidesWith(Dino& dino) {
    SDL_Rect dinoRect = { dino.x, dino.y, DINO_WIDTH, DINO_HEIGHT };  // Tạo hình chữ nhật bao quanh Dino
    SDL_Rect cactusRect = { x, y, width, height };  // Tạo hình chữ nhật bao quanh Cactus
    return SDL_HasIntersection(&dinoRect, &cactusRect);  // Trả về true nếu có va chạm
}