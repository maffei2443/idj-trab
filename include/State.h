#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include "InputManager.h"
// Class responsible for the game logic.
class State {
  private:
    Music music;
    GameObject* bg;
    bool quitRequested;
    std::vector<std::shared_ptr<GameObject>> objectArray;

    void AddObject(int mouseX, int mouseY);
    InputManager* inputManager = &InputManager::GetInstance();
    // t5
    bool started = false;

  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets(); // pré-carregar os assets do state do jogo
    // carregar imagens/fontes/músicas às suas variáveis aqui sempre
    // que for possível.
    void Update(double dt);
    void Render();

    // t5
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject*);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject*);
};

#endif