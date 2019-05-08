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


Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    new Sprite(this->associated, "assets/img/minion.png");
    
    // this->associated.box.SetXY(this->alienCenter.box.x, this->alienCenter.box.y);
    // int x = 40;
    this->associated.box.SetXY( Vec2(this->alienCenter.box + Vec2(60, 0)) ) ;
    // printf("MINION X,Y %lf %lf\n", this->alienCenter.box.x, this->alienCenter.box.y);
    
    cout << "Minion.associated --> " << &this->associated << endl;
    this->associated.AddComponent(this);
    printf("MINION BORN %p \n", this);
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
    cout << "Alien Center: " << this->alienCenter.box.center << endl;
    this->associated.box.SetXY(newPos.x, newPos.y);
}

void Minion::Render(){ 

}

bool Minion::Is(std::string){ 
    return type == "Minion";
}


// t5
void Minion::Shoot(Vec2) {

}

void Minion::Start() {

}