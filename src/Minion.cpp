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
    this->associated.box.x = this->alienCenter.box.x;
    this->associated.box.y = this->alienCenter.box.y;
    this->associated.box.center = this->alienCenter.box.center;
    
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

    // Vec2 newMinionPos(
    //     (this->associated.box.x - centerOfAlien.x),
    //     (this->associated.box.y - centerOfAlien.y)
    // );
    Vec2 newMinionPos = Vec2(this->associated.box.x, this->associated.box.y);
    // newMinionPos /= 10;
    newMinionPos.rotate( 0.01 );
    // newMinionPos.x = newMinionPos.x - 0.01;
    // newMinionPos.y = newMinionPos.y - 0.01;

    printf("alien center : x, y = %lf, %lf\n", centerOfAlien.x, centerOfAlien.y);
    this->associated.box.x = newMinionPos.x + 100000*centerOfAlien.x;

    this->associated.box.y = newMinionPos.y + 1000*centerOfAlien.y;

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