#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Renderer* TextureManager::rendererRef = nullptr;
std::unordered_map<std::string, SDL_Texture*> TextureManager::textures;

void TextureManager::SetRenderer(SDL_Renderer* ren) {
    rendererRef = ren;
}

void TextureManager::LoadTexture(const std::string& id, const std::string& filename) {
    SDL_Surface* tmpSurface = IMG_Load(filename.c_str());
    if (!tmpSurface) {
        printf(" Failed to load image %s: %s\n", filename.c_str(), IMG_GetError());
        return;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(rendererRef, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    if (!tex) {
        printf(" Failed to create texture from %s: %s\n", filename.c_str(), SDL_GetError());
        return;
    }

    textures[id] = tex;
}


SDL_Texture* TextureManager::GetTexture(const std::string& id) {
    return textures[id];
}
