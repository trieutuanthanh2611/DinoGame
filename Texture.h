#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

extern SDL_Renderer* renderer;
extern TTF_Font* font;

class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string path);
    bool loadFromText(std::string text, SDL_Color color);
    void free();
    void render(int x, int y, SDL_Rect* clip = nullptr, int w = 0, int h = 0);
    int getWidth();
    int getHeight();

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif