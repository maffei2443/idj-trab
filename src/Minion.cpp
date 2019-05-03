#include "Minion.h"
#include "GameObject.h"
#include "Vec2.h"
#include <memory>
using std::weak_ptr;
using std::string;
#include "Sprite.h"


Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg) : arc(arcOffsetDeg),Component(associated) {
    this->alienCenter = alienCenter;
    new Sprite(this->associated, "assets/img/minion.png");
    this->associated.box.x = 100;
    this->associated.box.y = 100;
    printf("Minion EXISTS\n");
}

Minion::~Minion () {

}

// herda de Component
void Minion::Update(double dt) {
    (void)dt;
    printf("[Minion.Update] %p\n", this);
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