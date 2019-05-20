#include <string>
#include <SDL2/SDL.h>
#include "Collider.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Camera.h"
#include "Game.h"
#include <iostream>
using std::cout;
using std::endl;
//#define DEBUG
const string Collider::type("Collider");

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated) {
    this->associated.AddComponent((this));
}

Collider::~Collider() {
    cout << "Collider died!" << endl;
}

void Collider::Update(double dt) {
    /* sete a box atual como uma cópia da box de associated mas com sua
largura e altura multiplicados por uma escala */
    this->box = this->associated.box;
    this->box.w *= this->scale.x;
    this->box.h *= this->scale.y;
    /* centro dela seja igual ao centro da box de associated */
    /* adicionado do atributo offset rotacionado pelo ângulo de associated. */
    this->box.SetCenter(this->associated.box.GetCenter() + this->offset);
}


void Collider::Render() {
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}



void Collider::Start() {
    this->started = true;
}
void Collider::NotifyCollision(GameObject& other) {
  (void)other;
  return;
}