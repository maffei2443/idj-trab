#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.h"
int AuxCodeErr = 0;
#define ABORT_IF_NZERO( x ) \
        AuxCodeErr = x; if (AuxCodeErr) myAbort(AuxCodeErr); else printf("Ok passed.\n");
#define ABORT_IF_ZERO( x ) \
        ABORT_IF_NZERO(!(x) )
// #include "SDL.h"
// #include "SDL_image.h"
// #include "SDL_mixer.h"
void myAbort(int err) {
    std::cerr << "Failed because of " << err << "\n";
    abort();
}
int tst() {
    printf("99!\n");
    return 99;
}
int main(int argc, char** argv)
{
    // Check http://wiki.libsdl.org/SDL_Init for explanation.
    // Tries to initialize SDL lib.
    ABORT_IF_NZERO(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER));    
    // Load img lib.
    // Returns bitmask equivalent to the loaders it loaded.
    ABORT_IF_NZERO(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF));    

    ABORT_IF_NZERO(!Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3));    
    ABORT_IF_NZERO(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024));
    ABORT_IF_NZERO(GAME_CHANNELS != Mix_AllocateChannels(GAME_CHANNELS));

    // SDL_CreateWindow(                 const char* title,      x,                  y,                     int width, int h, Uint32 flags);
    SDL_Window* window = SDL_CreateWindow("Meu Jogo daora", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280    , 720   , 0);


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    // TODO: take a look on http://wiki.libsdl.org/SDL_CreateWindow .(e.e, fullscreen)
    SDL_Texture* texture = IMG_LoadTexture(renderer, "resources/ocean.jpg");
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);

    SDL_Rect sourceRect = {0, 0, textureWidth, textureHeight};
    SDL_Rect onScreenRect = {0, 0, 1024, 600};
    SDL_RenderCopyEx(renderer, texture, &sourceRect, &onScreenRect, 0, nullptr, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    Mix_Music* music = Mix_LoadMUS("resources/Tema_Boss_01.wav");
    Mix_PlayMusic(music, 1);
    int i = 0;
    while(++i < 10000000){
        if(SDL_QuitRequested()){
            break;
        }
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}