#include "Minion.h"
#include "GameObject.h"
#include "Vec2.h"
#include <memory>
#include <iostream>
using std::weak_ptr;
using std::string;
using std::cout;
using std::endl;
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "Camera.h"

double angularSpeed = 0.02;

#include <chrono>
#include <random>
#include "Collider.h"
const static int FRAMES = 1;
const static double FRAME_TIME = 1000;

static std::default_random_engine randomGenerator;
static std::uniform_real_distribution<double> minionScale(1.0,1.5);

Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
  double arcOffsetDeg, Vec2 initPos) : arc(arcOffsetDeg),Component(associated), alienCenter(alienCenter) {
  this->mySprite = new Sprite(
    this->associated,
    "assets/img/minion.png",
    FRAMES,
    FRAME_TIME);
  this->mySprite->angleToRotate = 0.020;
  initPos.rotate(arcOffsetDeg);
  this->innerPos = initPos;

  double scale = minionScale(randomGenerator);
  auto alienCenterAccessor = this->alienCenter.lock().get();
  if(alienCenterAccessor) {
    this->associated.box.SetXYWH(
      alienCenterAccessor->box.GetCenter().x, 
      alienCenterAccessor->box.GetCenter().y, 
      mySprite->GetWidth()/* *scale */, 
      mySprite->GetHeight()/* *scale */
    ) ;
    // this->associated.box.AddX( arcOffsetDeg ); 
    this->associated.AddComponent(this);
    mySprite->SetScale(scale, scale);
  }
  new Collider(this->associated);
}

Minion::~Minion () {
  cout << "[" << this->GetType() << "] DESTRUCTOR" << endl;
  printf("MINION OF %p DYINGGGGGGGGGGGGGGG\n", this);
}

// herda de Component
void Minion::Update(double dt) {
    innerPos.rotate(angularSpeed * dt);
    
    auto alienCenterAccessor = this->alienCenter.lock().get();
    if(alienCenterAccessor) {
        Vec2 newPos =  innerPos + alienCenterAccessor->box.GetCenter();
        this->associated.box.SetCenter(newPos);
    }
    if(Camera::focus != &this->associated)
      this->associated.box -= Camera::speed;
    // cout << "??? : " << this->associated.box << endl;
    // OK funcionando
}

void Minion::Render(){ 
    
}

bool Minion::Is(string type){ 
    return type == "Minion";
}


// t5
void Minion::Shoot(Vec2 direction) {
  GameObject* GO_of_bullet = new GameObject;
  direction = direction - Vec2(this->associated.box.GetCenter());

  Vec2 vecNormalized = direction.unitary();
  Vec2 myPos = Vec2(this->associated.box);
  double angle = RAD2DEG * atan2(vecNormalized.y, vecNormalized.x) ;
  // cout << "Minion.associated.box == " << this->associated.box << endl;
  int damage = 0;
  double speed = 0.2;
  double maxDistance = 100000;
  new Bullet(*GO_of_bullet, angle, speed, damage, maxDistance,
      "assets/img/minionbullet2.png", 
      this->associated.box.GetCenter().x, this->associated.box.GetCenter().y);
  Game::GetInstance().GetState().AddObject(GO_of_bullet);
}

void Minion::Start() {
    this->started = true;
}

Rect Minion::GetBox() {
    return this->associated.box;
}


