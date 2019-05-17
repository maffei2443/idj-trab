#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Component.h"
// #include "Vec2.h"
#include <memory>
#include <string>
#include "Sprite.h"
#include "Game.h"
#include "InputManager.h"
#include "CameraFollower.h"
#include <algorithm>
#include <iostream>
using std::cout;
using std::endl;

using std::vector;
using std::weak_ptr;
using std::shared_ptr;
using std::string;

using std::max;
using std::min;

const double ACCELERATION = 0.001;
const double MAX_SPEED_X = 1.60;
const double MAX_SPEED_Y = 1.60;
const double MIN_SPEED_X = -1.0;
const double MIN_SPEED_Y = -1.0;

const string PenguinBody::type("PenguinBody");
PenguinBody* PenguinBody::player(nullptr);
static InputManager& inputManager = InputManager::GetInstance();

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    PenguinBody::player = this;
    this->associated.AddComponent(this);

    this->mySprite = new Sprite(this->associated, "assets/img/penguin.png");
    this->associatedSharedPtr = shared_ptr<GameObject>(&this->associated);
    this->associated.box.SetXYWH(704, 300, this->mySprite->GetWidth(), this->mySprite->GetHeight());
    new CameraFollower(this->associated);
  }
PenguinBody::~PenguinBody(){
  PenguinBody::player = nullptr;
  cout << "[" << this->GetType() << "] DESTRUCTOR" << endl;

}
void PenguinBody::Start() {
  this->started = true;
  GameObject* cannonGO = new GameObject();
  this->pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
  new PenguinCannon(*cannonGO, weak_ptr<GameObject>(this->associatedSharedPtr) );
  cout << "PENGUIN BODY TRUE STARTEDz\n";
}
void PenguinBody::Render() {
  // vazio para PenguinCannon e PenguinBody
}

bool PenguinBody::Is(string type) {
  return type == this->type;
}
void PenguinBody::Update(double dt) {
  (void)dt;
  bool w_down = inputManager.IsKeyDown('w');
  bool a_down = inputManager.IsKeyDown('a');
  bool s_down = inputManager.IsKeyDown('s');
  bool d_down = inputManager.IsKeyDown('d');
  if(w_down and not s_down) { // aceleracao positiva
    this->linearSpeed += ACCELERATION * dt;
  }
  else if(not w_down and s_down) {  // aceleracao negativa
    this->linearSpeed -= ACCELERATION * dt;
  }

  if (a_down or d_down) {
    Sprite * mySprite = ((Sprite*)this->associated.GetComponent("Sprite"));
    // mySprite->
    if(a_down and not d_down) {
      mySprite->RotateDt(dt, -0.12);
    }
    else if(not a_down and d_down) {
      mySprite->RotateDt(dt,0.12);
    }
  }
  this->speed = Vec2(1,0).GetRotated(this->mySprite->angleCurrent) * this->linearSpeed;
  // velocidade de acordo com o angulo do sprite

  this->associated.box.AddXY(
    this->speed.x*dt, this->speed.y*dt
  );
  if (this->hp <= 0) {
    this->associated.RequestDelete();
    this->pcannon.lock().get()->RequestDelete();
  }
}

