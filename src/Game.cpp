#define INCLUDE_SDL_IMAGE   // load img frm dsk
#define INCLUDE_SDL_MIXER   // load sng frm dsk
#include "Game.h"
#include <exception>

Game* Game :: instance = nullptr;

Game :: Game(std::string title, int width, int height ) {
  if (! (Game :: instance == nullptr) ) {
    throw ("Tried to instantiate more than one Game Object\n");
  }
  this->title = title;
  this->width = width;
  this->height = height;
  // Unique possible instance os Game. (Singleton Pattern)
  Game::instance = this;
}

Game& Game :: GetInstance() {
  if (Game :: instance != nullptr) {
    auto x = std::string("Meu jogo");
    Game :: instance = new Game(x, 1920, 1080);
  }
  return *Game :: instance;
} 