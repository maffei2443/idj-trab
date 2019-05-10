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
    double arcOffsetDeg, Vec2 initPos=Vec2(rand()%360, 0)) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    new Sprite(this->associated, "assets/img/minion.png");
    // this->associated.box.SetCenter(this->alienCenter.box.center);
    this->associated.box.SetCenter( this->alienCenter.box.center ) ;    
    this->associated.AddComponent(this);
    this->innerPos = initPos;
}

Minion::~Minion () {
    printf("MINION OF %p DYINGGGGGGGGGGGGGGG\n", this);
}

// herda de Component
void Minion::Update(double dt) {
    (void)dt;
    innerPos.rotate(0.07);
    Vec2 newPos =  innerPos + this->alienCenter.box.center ;
    // cout << "innerPos : " << innerPos << endl;
    this->associated.box.SetCenter(newPos);
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