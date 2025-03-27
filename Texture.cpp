#include "Texture.h"
#include <iostream>

Texture::Texture() : texture(nullptr), width(0), height(0) {}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile(std::string path) {
    free();
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path.c_str());
    if (newTexture == nullptr) {
        std::cout << "Unable to load texture: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_QueryTexture(newTexture, nullptr, nullptr, &width, &height);
    texture = newTexture;
    return true;
}

bool Texture::loadFromText(std::string text, SDL_Color color) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr) {
        std::cout << "Unable to render text surface: " << TTF_GetError() << std::endl;
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == nullptr) {
        std::cout << "Unable to create texture from text: " << SDL_GetError() << std::endl;
        return false;
    }
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);
    return true;
}

void Texture::free() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* clip, int w, int h) {
    SDL_Rect renderQuad = { x, y, w ? w : width, h ? h : height };
    if (clip != nullptr) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int Texture::getWidth() { return width; }
int Texture::getHeight() { return height; }