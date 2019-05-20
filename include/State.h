#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include "InputManager.h"
using std::weak_ptr;
using std::shared_ptr;
using std::vector;

#ifndef STR
#define STR(x) #x
#define PRINT(expr) cout << STR(expr) ": " << (expr) << endl;
#endif
// Class responsible for the game logic.
class State {
  private:
    const static string type;

    Music music;
    GameObject* bg;
    bool quitRequested;
    vector<shared_ptr<GameObject>> objectArray;

    void AddObject(int, int );
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
    weak_ptr<GameObject> AddObject(GameObject*);
    weak_ptr<GameObject> GetObjectPtr(GameObject*);
    void ResolveCollision();
    const inline string GetType() const {
      return this->type;
    }
    void NotifyCollision();
};

#endif