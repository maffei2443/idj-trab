#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>

// Class responsible for the game logic.
class CameraFollower {
  private:
    Music music;
    Sprite* bg;
    bool quitRequested;
    std::vector<std::shared_ptr<GameObject>> objectArray;

    void AddObject(int mouseX, int mouseY);
    void Input();
  
  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets(); // pré-carregar os assets do state do jogo
    // carregar imagens/fontes/músicas às suas variáveis aqui sempre
    // que for possível.
    void Update(double dt);
    void Render();
};

#endif