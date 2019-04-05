#include <iostream>
#include <string>
#include <stdexcept>
#include "Music.h"
#include "SDL_include.h"
#define INCLUDE_SDL_MIXER

Music :: Music() {
    this->music = nullptr;
}

Music :: Music(std::string file) {
    this->Open(file);
}

void Music :: Play(int times=-1) {
    // Se loops for -1, a música repete infinitamente. Se loops for 0, a música não é
    // tocada. Vale notar que a Mixer só suporta uma música sendo tocada por vez:
    // Se outra música já estiver tocando, ela para.
    const int TIMES_TO_PLAY = times;
    Mix_PlayMusic(this->music, TIMES_TO_PLAY);
}

void Music :: Stop(int msToStop = 1500) {
    Mix_FadeOutMusic(msToStop);
}

void Music :: Open(std::string file) {
    SDL_ClearError();
    this->music = Mix_LoadMUS( file.c_str() );
    std::cout << "After Music::Open ~~>" << SDL_GetError() << std::endl;

    // if (!err) {
    //     LOG(std::runtime_error("Error loading Music");
    // }
}

bool Music :: IsOpen() {
    return !!this->music;
}

Music :: ~Music() {
    this->Stop(0);
}

