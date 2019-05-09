#include "Bullet.h"
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
using std::string;


const string Bullet::type("Bullet");
Vec2 speed;
double distanceLeft;
int damage;


Bullet::Bullet(GameObject& associated, double angle, double speed, int damage,
double maxDistance, string sprite): Component(associated) {
    // this->speed = speed;

    this->distanceLeft = maxDistance;
    new Sprite(this->associated, sprite.c_str());
    this->associated.box.SetXY(0, 0);   // colocar na origem o bullet. Soh pra ver.
    this->associated.AddComponent(this);

}

void Bullet::Update(double dt) {

}

void Bullet::Render() {

}

bool Bullet::Is(const string& type) {
    return this->type == type;
}

int Bullet::GetDamage() {

}
