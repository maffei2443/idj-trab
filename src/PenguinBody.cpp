#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Component.h"
// #include "Vec2.h"
#include <memory>
#include <string>
#include "Sprite.h"
#include "Game.h"

using std::vector;
using std::weak_ptr;
using std::shared_ptr;
using std::string;

double acceleration = 0.02;

const string PenguinBody::type("PenguinBody");
PenguinBody* PenguinBody::player(nullptr);

PenguinBody::PenguinBody(GameObject& associated, weak_ptr<GameObject> weakGO) : 
  Component(*weakGO.lock().get()){
    PenguinBody::player = this;
    new Sprite(this->associated, "assets/img/penguin.png");
    this->associatedSharedPtr = shared_ptr<GameObject>(&this->associated);
  }
PenguinBody::~PenguinBody(){
  PenguinBody::player = nullptr;
}
void PenguinBody::Start() {
  this->started = true;
  GameObject* cannonGO = new GameObject();
  this->pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
  new PenguinCannon(*cannonGO, weak_ptr<GameObject>(this->associatedSharedPtr) );
}
void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
  return type == PenguinBody::type;
}
void PenguinBody::Update(double dt) {
  (void)dt;
  myAbort(12345);

}
// PenguinBody::(){}
// PenguinBody::(){}