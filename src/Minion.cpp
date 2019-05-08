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
    this->associated.box.SetXY(30, 30);
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
    this->associated.box /= 3;
    Vec2 centerOfAlien = this->alienCenter.box.center;

    // Vec2 newMinionPos(
    //     (this->associated.box.x - centerOfAlien.x),
    //     (this->associated.box.y - centerOfAlien.y)
    // );

    Vec2 pos = {this->associated.box.x, this->associated.box.y};
    pos.rotate(0.07);
    cout << "Pos : " << pos;
    pos *= 3;
    cout << "Alien Center: " << this->alienCenter.box.center << endl;
    this->associated.box.SetXY(pos.x, pos.y);
    // Vec2 newMinionPos = Vec2(this->associated.box.x, this->associated.box.y);

    // newMinionPos.rotate( 0.07 );


    // this->associated.box.x = (newMinionPos.x + centerOfAlien.x);
    printf("this->associated.box.x ------------ %lf\n", this->associated.box.x);
    // this->associated.box.x /= 2;
    printf("this->associated.box.x/2 ------------ %lf\n", this->associated.box.x/2);

    // this->associated.box.y = (newMinionPos.y + centerOfAlien.y);
    // printf("this->associated.box.y ------------ %lf\n", this->associated.box.y);

    // Vec2 newMinionPos(this->associated.box.x, this->associated.box.y);

    // newMinionPos.rotate( 0.01 );

    // Vec2 alienCenter = this->alienCenter.box.center;

    // this->associated.box.x = newMinionPos.x;

    // this->associated.box.y = newMinionPos.y;

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