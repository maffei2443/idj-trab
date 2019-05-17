#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Component.h"
// #include "Vec2.h"
#include <memory>
#include <string>
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include <algorithm>
using std::vector;
using std::weak_ptr;
using std::shared_ptr;
using std::string;

using std::max;
using std::min;

const double ACCELERATION = 0.05;
const double MAX_SPEED_X = 1.60;
const double MAX_SPEED_Y = 1.60;
const double MIN_SPEED_X = -1.0;
const double MIN_SPEED_Y = -1.0;

const string PenguinBody::type("PenguinBody");
PenguinBody* PenguinBody::player(nullptr);
static InputManager& inputManager = InputManager::GetInstance();

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
  // vazio para PenguinCannon e PenguinBody
}

bool PenguinBody::Is(string type) {
  return type == PenguinBody::type;
}
void PenguinBody::Update(double dt) {
  (void)dt;
  myAbort(12345);
  bool w_down = inputManager.IsKeyDown('w');
  bool a_down = inputManager.IsKeyDown('a');
  bool s_down = inputManager.IsKeyDown('s');
  bool d_down = inputManager.IsKeyDown('d');
  if(w_down and not s_down) { // aceleracao positiva
    Vec2 possibleNewSpeed = this->speed + ACCELERATION * dt;
    this->speed = Vec2(
      min(possibleNewSpeed.x, MAX_SPEED_X),
      min(possibleNewSpeed.y, MAX_SPEED_Y)
    );
  }
  else if(not w_down and s_down) {  // aceleracao negativa
    Vec2 possibleNewSpeed = this->speed - ACCELERATION * dt;
    this->speed = Vec2(
      max(possibleNewSpeed.x, MIN_SPEED_X),
      max(possibleNewSpeed.y, MIN_SPEED_Y)
    );
  }

  if (a_down or d_down) {
    Sprite * mySprite = ((Sprite*)this->associated.GetComponent("Sprite"));
    // mySprite->
    if(a_down and not d_down) {
      // rotacionar para a esquerda
      mySprite->RotateDt(dt, 0.12);
    }
    else if(not a_down and d_down) {
      // rotacionar para a esquerda
      mySprite->RotateDt(dt,-0.12);
    }
  }
  this->associated.box = this->associated.box + this->speed * dt;
  if (this->hp <= 0) {
    this->associated.RequestDelete();
    this->pcannon.lock().get()->RequestDelete();
  }
}
// PenguinBody::(){}
// PenguinBody::(){}