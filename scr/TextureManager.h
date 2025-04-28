#include <unordered_map>
#include <string>
#include <SDL.h>

class TextureManager {
public:
    static void SetRenderer(SDL_Renderer* ren);
    static void LoadTexture(const std::string& id, const std::string& filename);
    static SDL_Texture* GetTexture(const std::string& id);

private:
    static SDL_Renderer* rendererRef;
    static std::unordered_map<std::string, SDL_Texture*> textures;
};
