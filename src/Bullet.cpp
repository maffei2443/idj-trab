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
using std::cerr;

const string Bullet::type("Bullet");
Vec2 speed;
double distanceLeft;
int damage;


Bullet::Bullet(GameObject& associated, double angle, double speed, int damage,
double maxDistance, string sprite): Component(associated) {
    (void)maxDistance;
    (void)speed;
    (void)damage;
    cout << "BULLET ON" << endl;
    this->distanceLeft = 1000000;
    
    this->associated.AddComponent(
        new Sprite(this->associated, sprite.c_str())
    );
    this->associated.AddComponent(this);
    this->associated.box.SetXY(200, 200);   // colocar na origem o bullet. Soh pra ver.
    
    // cout << "Bullet speed [0] : " << this->speed << endl;

    this->speed = Vec2(1,0);    // base speed
    // cout << "Bullet speed [1] : " << this->speed << endl;
    this->speed.rotate(angle);

    // cout << "Bullet speed [2] : " << this->speed << endl;
    // cout << "Bullet speed.unitary() [2] : " << this->speed.unitary() << endl;
    this->speed = this->speed.unitary() * (double)0.01;
    // this->speed = {0.01, 0.01};
    cout << "Bullet speed [3] : " << this->speed << endl;
    // abort();
}
Bullet::~Bullet() {
    cout << "[Bullet] MORTO" << endl;
    myAbort(111222);
}
void Bullet::Update(double dt) {
    // cout << "BULLET UPUPUP\n";
    (void)dt;
    // cout << "BULLET UPDATING\n";
    // todo : add robusteza (i.e, impedir que a bala passe do ponto)
    if(this->distanceLeft > 0) {
        this->associated.box += this->speed;
        this->distanceLeft -= this->speed.abs();
        // this->associated.RequestDelete();
    }
    else {
        this->associated.RequestDelete();
        // myAbort(11);

        // this->distanceLeft -= (speed*;
    }
    // cout << "BULLET UPDATE << " << this << endl;
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