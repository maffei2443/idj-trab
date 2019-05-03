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
    printf("[Minion.Update] %p\n", this);
    this->associated.box.x = this->alienCenter.box.x;
    this->associated.box.y = this->alienCenter.box.y;

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