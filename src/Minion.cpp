#include "Minion.h"
#include "GameObject.h"
#include "Vec2.h"
#include <memory>
using std::weak_ptr;
using std::string;
#include "Sprite.h"


Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    new Sprite(this->associated, "assets/img/minion.png");
    this->associated.box.x = 100;
    this->associated.box.y = 100;
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

}


// t5
void Minion::Shoot(Vec2) {

}

void Minion::Start() {

}