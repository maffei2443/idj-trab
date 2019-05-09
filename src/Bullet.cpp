#include "Bullet.h"
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include <iostream>
#include "Macros.h"
using std::string;
using std::cout;
using std::endl;

const string Bullet::type("Bullet");
Vec2 speed;
double distanceLeft;
int damage;


Bullet::Bullet(GameObject& associated, double angle, double speed, int damage,
double maxDistance, string sprite): Component(associated) {
    cout << "BULLET ON" << endl;
    this->distanceLeft = maxDistance;
    
    new Sprite(this->associated, sprite.c_str());
    this->associated.AddComponent(this);
    this->associated.box.SetXY(200, 200);   // colocar na origem o bullet. Soh pra ver.
    

    this->speed = Vec2(1,0);    // base speed
    this->speed.rotate(angle);
    this->speed = this->speed.unitary() * speed;
    this->speed = {0, 0};
}
Bullet::~Bullet() {
    myAbort(111222);
}
void Bullet::Update(double dt) {
    // todo : add robusteza (i.e, impedir que a bala passe do ponto)
    if(this->distanceLeft > 0) {
        this->associated.box += this->speed;
        this->distanceLeft -= this->speed.abs();
    }
    else {
        this->associated.RequestDelete();
        // this->distanceLeft -= (speed*;
    }
    cout << "BULLET UPDATE << " << this << endl;
}

void Bullet::Render() {

}

bool Bullet::Is(string type) {
    return this->type == type;
}

int Bullet::GetDamage() {
    return this->damage;
}

void Bullet::Start() {
    this->started = true;
}