#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

// Class responsible for the game logic.
class State {
  private:
    Sprite bg;
    Music music;
    bool quitRequested;
  public:
    State();
    bool QuitRequested();
    void LoadAssets(); // pré-carregar os assets do state do jogo
    // carregar imagens/fontes/músicas às suas variáveis aqui sempre
    // que for possível.
    void Update(double dt);
    void Render();
    void Input();
};

#endif