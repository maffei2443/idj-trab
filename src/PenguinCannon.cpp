#include "PenguinCannon.h"

const string PenguinCannon::type("PenguinCannon");


PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) :
  Component(associated), pbody(penguinBody){
    this->angle = 0.0;
}
void PenguinCannon::Start() {
  this->started = true;
}
void PenguinCannon::Update(double dt) {

}
void PenguinCannon::Render() {

}
bool PenguinCannon::Is(string type) {
  return type == PenguinCannon::type;
}
// PenguinCannon::(){}