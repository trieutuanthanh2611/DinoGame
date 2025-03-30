#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

extern SDL_Renderer* renderer;  // Renderer toàn cục
extern TTF_Font* font;          // Font toàn cục

// Lớp quản lý texture (hình ảnh hoặc văn bản)
class Texture {
public:
    Texture();      // Constructor
    ~Texture();     // Destructor

    bool loadFromFile(std::string path);  // Tải texture từ file
    bool loadFromText(std::string text, SDL_Color color);  // Tải texture từ văn bản
    void free();  // Giải phóng tài nguyên
    void render(int x, int y, SDL_Rect* clip = nullptr, int w = 0, int h = 0);  // Vẽ texture
    int getWidth();  // Lấy chiều rộng
    int getHeight(); // Lấy chiều cao

private:
    SDL_Texture* texture;  // Con trỏ đến texture SDL
    int width;             // Chiều rộng của texture
    int height;            // Chiều cao của texture
};

#endif