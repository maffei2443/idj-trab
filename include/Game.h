#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include "State.h"
#include "Macros.h"

#define INCLUDE_SDL // main. sdl. func
#include "SDL_include.h"
#include <string>
using std::string;

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
    string title;    
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    int frameStart;
    double dt;
    static Game* instance;    
    static const string type;

    Game(string title, int width, int height, int freq, unsigned short format, int channels );
    void CalculateDeltaTime();
  public:
    ~Game();
    static Game& GetInstance();
    State& GetState();
    SDL_Renderer* GetRenderer();
    void Run();
    
    string GetType() {
      return this->type;
    }
    int GetHeight() {
      return this->height;
    }
    int GetWidth() {
      return this->width;
    }
};

#endif