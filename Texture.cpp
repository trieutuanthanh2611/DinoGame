#include "Texture.h"
#include <iostream>

// Constructor cho lớp Texture, khởi tạo rỗng
Texture::Texture() : texture(nullptr), width(0), height(0) {}

// Destructor để giải phóng tài nguyên
Texture::~Texture() {
    free();  // Giải phóng texture
}

// Tải texture từ file hình ảnh
bool Texture::loadFromFile(std::string path) {
    free();  // Giải phóng texture cũ nếu có
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());  // Tải texture từ đường dẫn
    if (newTexture == nullptr) {  // Kiểm tra lỗi
        std::cout << "Unable to load texture: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_QueryTexture(newTexture, nullptr, nullptr, &width, &height);  // Lấy kích thước texture
    texture = newTexture;  // Gán texture mới
    return true;
}

// Tải texture từ văn bản
bool Texture::loadFromText(std::string text, SDL_Color color) {
    free();  // Giải phóng texture cũ nếu có
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);  // Tạo bề mặt văn bản
    if (textSurface == nullptr) {  // Kiểm tra lỗi
        std::cout << "Unable to render text surface: " << TTF_GetError() << std::endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);  // Chuyển bề mặt thành texture
    if (texture == nullptr) {  // Kiểm tra lỗi
        std::cout << "Unable to create texture from text: " << SDL_GetError() << std::endl;
        return false;
    }
    width = textSurface->w;  // Lấy chiều rộng
    height = textSurface->h;  // Lấy chiều cao
    SDL_FreeSurface(textSurface);  // Giải phóng bề mặt
    return true;
}

// Giải phóng tài nguyên texture
void Texture::free() {
    if (texture != nullptr) {  // Nếu texture tồn tại
        SDL_DestroyTexture(texture);  // Hủy texture
        texture = nullptr;  // Đặt lại về nullptr
        width = 0;  // Đặt lại chiều rộng
        height = 0;  // Đặt lại chiều cao
    }
}

// Vẽ texture lên màn hình
void Texture::render(int x, int y, SDL_Rect* clip, int w, int h) {
    SDL_Rect renderQuad = { x, y, w ? w : width, h ? h : height };  // Tạo vùng vẽ
    if (clip != nullptr) {  // Nếu có vùng cắt
        renderQuad.w = clip->w;  // Sử dụng chiều rộng của vùng cắt
        renderQuad.h = clip->h;  // Sử dụng chiều cao của vùng cắt
    }
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);  // Sao chép texture lên renderer
}

// Lấy chiều rộng của texture
int Texture::getWidth() { return width; }

// Lấy chiều cao của texture
int Texture::getHeight() { return height; }