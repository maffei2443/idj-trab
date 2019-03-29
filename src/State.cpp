#include "State.h"
#include "Sprite.h"
#define INCLUDE_SDL
#include "SDL_include.h" // SDL_*
#include <string>
State :: State() : bg(Sprite("assets/img/lose.jpg")),
                   music(Music("assets/audio/stageState.ogg")) {
  // O construtor de State inicializa quitRequested e instancia o Sprite,
  this->quitRequested = false;
  this->music.Play(-1);
  // Instanciar o Sprite
  // this->bg = Sprite("assets/img/lose.jpg");
  // this->music = Musicl();
}

void State :: Update(double dt) {
  this->quitRequested = SDL_QuitRequested();
}

//  trata da etapa 4 de Game::Run
void State :: Render() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
  // printf("Before State.Render\n");
  this->bg.Render(0,0);
}

bool State :: QuitRequested() {
  return this->quitRequested;
}

void State :: LoadAssets() {
  //  Para esse trabalho, chame o render do fundo (bg). [?]
}
