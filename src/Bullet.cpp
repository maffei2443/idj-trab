#include "Bullet.h"
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include <iostream>
#include "Macros.h"
#include "InputManager.h"
#include "Util.h"
#include "Collider.h"
#include "Camera.h"
using std::string;
using std::cout;
using std::endl;
using std::cerr;

const string Bullet::type("Bullet");
Vec2 speed;
double distanceLeft;
int damage;
const int VEL = 3;
static InputManager& inputManager = InputManager::GetInstance();
// t6
const static int FRAMES = 3;
const static double FRAME_TIME = 10;



void Bullet::UpdatePosAndSpeed() {
    cout << "UPDATE BUUUULLET SPEEEED\n";
    if (true) {
        Sprite * mySprite = ((Sprite*)this->associated.GetComponent("Sprite"));
        double midX = (this->associated.box.x + (double)mySprite->GetWidth()/2);
        double midY = (this->associated.box.y + (double)mySprite->GetHeight()/2);

        double deltaX = -(midX-this->click.x);
        double deltaY = -(midY-this->click.y);

        double absDeltaX = fabs(deltaX);
        double absDeltaY = fabs(deltaY);

        double slope = deltaY / deltaX;
        double slopeInverse = deltaX / deltaY;
        
        Vec2 old_speed = this->speed;

        if (IsFloatZero(deltaX) or IsFloatZero(deltaY)) {
            this->gotoTarget(mySprite);
        }
        else {
            if(absDeltaX < absDeltaY) { // velocidade em X deve ser MENOR em modulo
                this->speed.y = (deltaY > 0 ? VEL : -VEL);
                this->speed.x = this->speed.y * slopeInverse ;  // 
            }
            else {
                this->speed.x = (deltaX > 0 ? VEL : -VEL);
                this->speed.y = this->speed.x * slope;
            }
            // checar se vai ir para onde estava antes. Se sim, pare de se mover e teleporta ao ponto objetivo.
            if(IsDoubleDiffZero( (this->associated.box-old_speed).abs(), (this->associated.box+this->speed).abs() ) )  {
                this->gotoTarget(mySprite);
            }
            else {
                this->associated.box.SetXY(this->associated.box.x + this->speed.x, this->associated.box.y + this->speed.y);
                // cout << "NOT NOT NOT NOT" << endl;
            }
        }
    }
    else
        // myAbort(1221)
        ;
    // cout << "THIS --> SPEED ===> " << this->speed << endl;

}

void Bullet::UpdatePos(double dt) {
    // cout << "UPDATE BUUUULLET POS\n";
    this->associated.box += (this->speed * dt);
    this->associated.box.UpdateCenter();
}

void Bullet::gotoTarget(Sprite* sprite) {
    this->speed.x = this->speed.y = 0;
    this->click.targetX = this->click.targetY = false;
    this->associated.box.SetCenter(
        this->click.x,
        this->click.y);
}

void Bullet::SetTarget(int x, int y) {
    this->click.x = x;    this->click.y = y;
    this->click.targetX = this->click.targetY = true;
}

Bullet::Bullet(GameObject& associated, double angle, double speed, int damage,
double maxDistance, string sprite, int x, int y, bool targetsPlayer): Component(associated) {
    (void)maxDistance;    (void)speed;
    this->targetsPlayer = targetsPlayer;
    this->distanceLeft = 1300;
    this->mySprite = new Sprite(
        this->associated, sprite.c_str(),
        FRAMES,
        100);
    this->associated.AddComponent(
        this->mySprite
    );
    this->associated.AddComponent(this);
    // cout << "target : " << target << endl;
    // myAbort(101);
    this->associated.box.SetXY(Vec2(x,y));
    this->mySprite->angleCurrent = 
        angle ;
    this->associated.angleDeg = angle;
    // cout << "Target: " << this->target << endl;
    // cout << "[Bulltet.cpp:99] MyCenter: " << this->associated.box.GetCenter() << endl;
    // cout << "this->mySprite->angleCurrent =  >> " << this->mySprite->angleCurrent  << endl;

    // myAbort(12);
    this->speed = Vec2(1,0);    // base speed
    this->speed.rotate(angle);
    this->damage = damage;
    this->speed = this->speed.unitary() * speed;
    new Collider(this->associated);
}
Bullet::~Bullet() {
    cout << "[" << this->GetType() << "] DESTRUCTOR" << endl;
}
void Bullet::Update(double dt) {
    // todo : add robusteza (i.e, impedir que a bala passe do ponto)
    if(this->distanceLeft > 0) {
        this->distanceLeft -= this->speed.abs();
        this->UpdatePos(dt);
        if(Camera::focus  != &this->associated)
            this->associated.box -= Camera::focus->GetSpeed()*dt;
    }
    else {
        this->associated.RequestDelete();
    }
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

void Bullet::NotifyCollision(GameObject& other) {
  /* Se uma Bullet colide com Penguins ou Alien, ela some...
  MAS soh se acertar algo que ela estah buscando */
  if(other.GetComponent("Bullet")) {
      return;
    // bullet com bullet nao faz nada por enquanto
  }
  if(other.GetComponent("Alien") and not this->targetsPlayer) {
    this->associated.RequestDelete();
  }
  else if(other.GetComponent("PenguinBody") and this->targetsPlayer) {
    this->associated.RequestDelete();
  }
}