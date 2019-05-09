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

Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg, const Vec2& vec) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    new Sprite(this->associated, "assets/img/minion.png");

    this->associated.box.SetXY( Vec2(this->alienCenter.box + vec ) ) ;    
    this->associated.AddComponent(this);
    
    GameObject* GO_of_bullet = new GameObject;
    new Bullet(*GO_of_bullet, 90.0, 0.0, 1, 0, "assets/img/minionbullet1.png");
    Game::GetInstance().GetState().AddObject(GO_of_bullet);
}

Minion::~Minion () {
    printf("MINION OF %p DYINGGGGGGGGGGGGGGG\n", this);
}

// herda de Component
void Minion::Update(double dt) {
    (void)dt;
    Vec2 newPos = Vec2(this->associated.box - this->alienCenter.box);
    newPos.rotate(0.07);
    newPos = this->alienCenter.box + newPos;
    // cout << "Alien Center: " << this->alienCenter.box.center << endl;
    this->associated.box.SetXY(newPos);
    // cout << "MinionCenter: " << this->associated.box.center << endl;
}

void Minion::Render(){ 
    
}

bool Minion::Is(string type){ 
    return type == "Minion";
}


// t5
void Minion::Shoot(Vec2 direction) {
}

void Minion::Start() {

}