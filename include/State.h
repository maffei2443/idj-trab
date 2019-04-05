#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr

// Class responsible for the game logic.
class State {
  private:
    Music music;
    Sprite* bg;
    bool quitRequested;

    void AddObject(int mouseX, int mouseY);
    // Para administrar os objetos instanciados no jogo,
    // vamos manter um
    // array de ponteiros para GOs.
    std::vector<std::unique_ptr<GameObject>> objectArray;
  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets(); // pré-carregar os assets do state do jogo
    // carregar imagens/fontes/músicas às suas variáveis aqui sempre
    // que for possível.
    void Update(double dt);
    void Render();
    void Input();
};

#endif