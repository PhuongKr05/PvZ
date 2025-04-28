#pragma once
#include <unordered_map>
#include <string>
#include <SDL_mixer.h>

class SoundManager {
public:
    static void Init();
    static void PlayMusic(const std::string& id);
    static void PlaySound(const std::string& id);
    static void Clean();

private:
    static std::unordered_map<std::string, Mix_Music*> musicTracks;
    static std::unordered_map<std::string, Mix_Chunk*> soundEffects;
};
