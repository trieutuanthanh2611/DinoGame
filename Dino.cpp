#include "Dino.h"
#include "Constants.h"

// Constructor cho đối tượng Dino, khởi tạo vị trí ban đầu và các thuộc tính vật lý
Dino::Dino() : x(50), y(SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT), velocity(0), acceleration(0.3f), jumping(false) {
    // x, y: Vị trí ban đầu của Dino (ở góc trái dưới màn hình)
    // velocity: Tốc độ di chuyển theo chiều dọc (ban đầu là 0)
    // acceleration: Gia tốc trọng lực (giúp Dino rơi xuống)
    // jumping: Trạng thái nhảy (ban đầu là false)
}

// Cập nhật trạng thái của Dino (xử lý nhảy và rơi)
void Dino::update() {
    if (jumping) {  // Nếu Dino đang nhảy
        y += static_cast<int>(velocity);  // Cập nhật vị trí Y dựa trên tốc độ
        velocity += acceleration;  // Tăng tốc độ để mô phỏng trọng lực
        if (y >= SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT) {  // Nếu chạm đất
            y = SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT;  // Đặt lại vị trí về mặt đất
            jumping = false;  // Kết thúc trạng thái nhảy
            velocity = 0;  // Đặt lại tốc độ về 0
        }
    }
}

// Xử lý hành động nhảy của Dino
void Dino::jump() {
    if (!jumping) {  // Chỉ cho nhảy nếu không đang nhảy
        jumping = true;  // Bật trạng thái nhảy
        velocity = -8.0f;  // Đặt tốc độ ban đầu để nhảy lên (âm vì di chuyển lên)
    }
}