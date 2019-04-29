#include "Minion.h"
#include "GameObject.h"
#include "Vec2.h"
#include <memory>
using std::weak_ptr;
using std::string;


Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
float arc) : Component(associated) {
    this->alienCenter = alienCenter.lock();
}

~Minion::Minion () {

}

// herda de Component
void Minion::Update(double dt) {

}
void Minion::Render(){ 

}

bool Minion::Is(std::string){ 

}


const inline std::string GetType(){
    return this->type;
}
// t5
void Shoot(Vec2);