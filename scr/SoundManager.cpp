#include "SoundManager.h"
#include <iostream>

std::unordered_map<std::string, Mix_Music*> SoundManager::musicTracks;
std::unordered_map<std::string, Mix_Chunk*> SoundManager::soundEffects;

void SoundManager::Init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << " SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    //nhạc nền
    musicTracks["bgm"] = Mix_LoadMUS("audio/Loonboon.mp3");

    //hiệu ứng âm thanh
    soundEffects["shoot"] = Mix_LoadWAV("audio/firepea.mp3");
    soundEffects["shovel"] = Mix_LoadWAV("audio/shovel.mp3");
    soundEffects["sun"] = Mix_LoadWAV("audio/sun_click.mp3");
    soundEffects["zombie_eat"] = Mix_LoadWAV("audio/zombie_eating2.mp3");

    std::cout << "SoundManager Initialized\n";
}

void SoundManager::PlayMusic(const std::string& id) {
    if (musicTracks[id]) {
        Mix_PlayMusic(musicTracks[id], -1);   // Phát lặp vô hạn
    }
    else {
        std::cout << "Music ID not found: " << id << std::endl;
    }
}

void SoundManager::PlaySound(const std::string& id) {
    if (soundEffects[id]) {
        Mix_PlayChannel(-1, soundEffects[id], 0);  // Phát 1 lần
    }
    else {
        std::cout << "Sound ID not found: " << id << std::endl;
    }
}

void SoundManager::Clean() {
    for (auto& m : musicTracks) {
        Mix_FreeMusic(m.second);
    }
    for (auto& s : soundEffects) {
        Mix_FreeChunk(s.second);
    }
    Mix_CloseAudio();
    std::cout << "SoundManager Cleaned\n";
}
