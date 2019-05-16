#include "PenguinCannon.h"
#include "Macros.h"
#include <memory>
#include "InputManager.h"

using std::weak_ptr;
const string PenguinCannon::type("PenguinCannon");
static InputManager& inputManager = InputManager::GetInstance();


PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) :
  Component(associated), pbody(penguinBody){
    this->angle = 0.0;
}

PenguinCannon::~PenguinCannon(){}

void PenguinCannon::Start() {
  this->started = true;
}
void PenguinCannon::Update(double dt) {
  (void)dt;
  // if(not penguinBody::player)
  //   this->associated.RequestDelete();
  // else {
  //   this->associated.box.SetCenter(
  //     penguinBody::player->associated.box.GetCenter()
  //   );
  //   Vec2 target(inputManager.GetMouseX(), inputManager.GetMouseY());
  //   Vec2 
  //   // ver angulo entre target e o centro da box, para atirar
  //   this->mySprite.Rotate();
  // }
  // myAbort(54321);
}
void PenguinCannon::Render() {

}
bool PenguinCannon::Is(string type) {
  return type == PenguinCannon::type;
}
// PenguinCannon::(){}

