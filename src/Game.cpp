#ifndef GAME_CPP
#define GAME_CPP

#define INCLUDE_SDL_IMAGE   // load img frm dsk
#define INCLUDE_SDL_MIXER   // load sng frm dsk
#include "Macros.h"
#include "Game.h"
#include "Constants.h"
#include <exception>
#include <cstdio>
#include <unistd.h>


Game* Game :: instance = nullptr;

Game :: Game(std::string title, int width, int height,
              int freq = MIX_DEFAULT_FREQUENCY,
              unsigned short format = MIX_DEFAULT_FORMAT,
              int channels = MIX_DEFAULT_CHANNELS) {
  this->freq = freq;
  this->format = format;
  this->channels = channels;
  if (! (Game :: instance == nullptr) )
    throw ("Tried to instantiate more than one Game Object\n");
  this->title = title, this->width = width, this->height = height;
  Game::instance = this;

  // Check http://wiki.libsdl.org/SDL_Init for explanation.
  // Tries to initialize SDL lib.
  // If fails, can use SDL_GetError to know the cause
  SDL_ABORT_IF_NZERO(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER));    
  // Load img lib.
  // Returns bitmask equivalent to the loaders it loaded.
  // IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  // TODO: take a look on http://wiki.libsdl.org/SDL_CreateWindow .(e.e, fullscreen)
  SDL_ABORT_IF_ZERO(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF));    

  // Load song lib.
  SDL_ABORT_IF_NZERO(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
    MIX_DEFAULT_CHANNELS, 1024));
  SDL_ABORT_IF_ZERO(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3));    
  
  SDL_ABORT_IF_ZERO(GAME_CHANNELS == Mix_AllocateChannels(GAME_CHANNELS));
  // se SDL_CreateWindow ou SDL_CreateRenderer falham, retornam nullptr
  // SDL_CreateWindow(                 const char* title,      x,                  y,                     int width, int h, Uint32 flags);
  this->window = SDL_CreateWindow("Leonardo Maffei da Silva 160033811", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height , 0);
  SDL_ABORT_IF_ZERO(window);
  // SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags)
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_ABORT_IF_ZERO(renderer);
  // Unique possible instance os Game. (Singleton Pattern)
  
  this->state = new State();
}

Game :: ~Game() {
  // delete this->state
  SDL_DestroyRenderer(this->renderer);
  // Destroy renderer and window.
  SDL_DestroyWindow(this->window);
  // Finish the music.
  // Mix_QuerySpec to find out how many times
  // Mix_CloseAudio needs to be called 

  int times = Mix_QuerySpec(&this->freq, &this->format, &this->channels);
  for(int i=0; i < times; i++)
    Mix_CloseAudio();
  Mix_Quit();

  // Finish the image.
  IMG_Quit();

  SDL_Quit();
 
}

Game& Game :: GetInstance() {
  if (Game :: instance == nullptr) {
    auto x = std::string("Meu jogo");
    Game :: instance = new Game(x, 1024, 600);
  }
  return *instance;
}

State& Game :: GetState() {
  return *this->state;
}

SDL_Renderer* Game :: GetRenderer() {
  return this->renderer;
}
void Game :: Run() {
  // TODO : gameloop
  // 1. Verifica, controla e carrega as telas de jogo;

  // 2. Os dados de input são recebidos e processados;

  // 3. Os objetos tem seus respectivos estados (posição, HP…)
  // atualizados;
  
  // 4. Os objetos são desenhados na tela
  int i = 0;
  while (!this->state->QuitRequested()) {
    printf("Before game->staate->Update\n");
    this->state->Update(0.0);  // Ok, debugging...
    printf("Before game->staate->Render\n");
    this->state->Render();
    printf("Before SDL_RenderPresent( this->renderer )\n");
    SDL_ClearError();
    SDL_RenderPresent( this->renderer );
    // printf("Error afet Render Present -->  %s\n", SDL_GetError());
    //  impor um limite de frame rate ao jogo.
    printf("Before SDL_Delay(Const::DELAY)\n");
    SDL_Delay(Const::DELAY);
    // sleep(1);
    i++;
  }
}

#endif