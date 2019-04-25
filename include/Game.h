#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "State.h"
#include "Macros.h"

#define INCLUDE_SDL // main. sdl. func
#include "SDL_include.h"

#define GAME_CHANNELS 32
// TODO: Create class to store "magic numbers" constants

class Game {
  private:   
    //  Used by Mix_QuerySpec after (know how many times should call
    // Mix_CloseAudio)
    int freq;
    Uint16 format;
    int channels;

    int width;
    int height;
    std::string title;

    
    Game(std::string title, int width, int height, int freq, unsigned short format, int channels );
    static Game* instance;    
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    // Novos mebros de Game (T4)
    int frameStart;
    float dt;
    void CalculateDeltaTime();
  public:
    // GetDEltaTime() add p/ T4
    int GetDeltaTime();
    
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();

};

#endif