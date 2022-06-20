#include "SDL_exception.h"
#include "music.h"

Music::Music() : music(nullptr) {}

Music::Music(string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
}

void Music::Play(int times) {
    if (music == nullptr) throw SDL_Exception();

    Mix_PlayMusic(music, times);
}

void Music::Stop(int ms) {
    Mix_FadeOutMusic(ms);
}

void Music::Open(string file) {
    music = Mix_LoadMUS(file.c_str());
}

bool Music::IsOpen() {
    return music != nullptr;
}