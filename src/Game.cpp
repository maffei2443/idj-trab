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
#include "Macros.h"
#include "Resources.h"
#include "InputManager.h"
#include <string>
using std::string;
Game* Game::instance = nullptr;
const string Game::type("Game");
Game::Game(string title, int width, int height,
              int freq = MIX_DEFAULT_FREQUENCY,
              unsigned short format = MIX_DEFAULT_FORMAT,
              int channels = MIX_DEFAULT_CHANNELS) {
  
  this->freq = freq;
  this->format = format;
  this->channels = channels;
  if ( (Game::instance) != nullptr )
    LOG(("Tried to instantiate more than one Game Object\n"));
  this->title = title, this->width = width, this->height = height;
  Game::instance = this;
  // Tries to initialize SDL lib.
  SDL_ABORT_IF_NZERO(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER));    
  // Load img lib.
  // Returns bitmask equivalent to the loaders it loaded.
  // IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  // TODO: take a look on http://wiki.libsdl.org/SDL_CreateWindow .(e.e, fullscreen)
  SDL_ABORT_IF_ZERO(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF));    
  
  SDL_ABORT_IF_NZERO(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
    MIX_DEFAULT_CHANNELS, 1024));
  
  SDL_ABORT_IF_ZERO(Mix_Init(MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3));      
  
  SDL_ABORT_IF_ZERO(GAME_CHANNELS == Mix_AllocateChannels(GAME_CHANNELS));
  // se SDL_CreateWindow ou SDL_CreateRenderer falham, retornam nullptr
  this->window = SDL_CreateWindow("Leonardo Maffei da Silva 160033811", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height , 0);
  
  SDL_ABORT_IF_ZERO(this->window);
  
  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
  
  SDL_ABORT_IF_ZERO(renderer);
  this->state = new State();
}

Game::~Game() {
  cout << "[" << this->GetType() << "] DESTRUCTOR" << endl;

  delete this->state;
  // Destroy renderer and window.
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  // Finish the music.
  // Mix_QuerySpec to find out how many times
  // Mix_CloseAudio needs to be called 
  int times = Mix_QuerySpec(&this->freq, &this->format, &this->channels);
  for(int i=0; i < times; i++)
    Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit(); 
}

Game& Game::GetInstance() {
  if (Game::instance == nullptr) {
    auto x = string("Leonardo Maffei da Silva - 16/0033811");
    Game::instance = new Game(x, 1024, 600);
  }
  return *instance;
}

State& Game::GetState() {
  return *this->state;
}

SDL_Renderer* Game::GetRenderer() {
  return this->renderer;
}
void Game::Run() {
  /* t5
  Em Game::Run, chame o Start do State logo antes do while. */
  InputManager* inputManager = &InputManager::GetInstance();
  this->state->Start();
  // printf("STATE.START FINISHED \n");
  while (not this->state->QuitRequested()) {
/* Agora, vamos integrar o InputManager ao programa. Acrescente uma
chamada ao método Update em Game::Run(), logo antes da chamada ao
update do estado */
    this->CalculateDeltaTime();
    inputManager->Update();
    this->state->Update(this->dt);  // Ok, debugging...
    this->state->Render();
    SDL_ClearError();
    SDL_RenderPresent( this->renderer );
    //  impor um limite de frame rate ao jogo.
    // SDL_Delay(Const::DELAY);
  }
  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
}

void Game::CalculateDeltaTime() {
  /* Atualizamos frameStart e usamos o valor antigo e
  o novo para calcular dt em milissegundos. */
  int oldFrameStart = this->frameStart; 
  this->frameStart = SDL_GetTicks ();
  this->dt = this->frameStart - oldFrameStart;
  using std::cout, std::endl;
  // cout << "dt --> " << dt << endl;
  // converta para segundos
  // this->dt = (int)(round(this->dt / 1000));
}


#endif