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
    int x = 40;
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
    // printf("[Minion.Update] %p\n", this);
    Vec2 centerOfAlien = this->alienCenter.box.center;

    // Vec2 pos = {this->associated.box.x - this->alienCenter.box.x
    //             , this->associated.box.y - this->alienCenter.box.y};
    Vec2 pos = Vec2(this->associated.box - this->alienCenter.box);  // METODO ESTAH BUGADO
    pos.rotate(0.07);
    pos = this->alienCenter.box + pos;
    cout << "Alien Center: " << this->alienCenter.box.center << endl;
    this->associated.box.SetXY(pos.x, pos.y);
    // printf("this->associated.box.x ------------ %lf\n", this->associated.box.x);
    // printf("this->associated.box.x/2 ------------ %lf\n", this->associated.box.x/2);
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