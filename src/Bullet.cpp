#include "Bullet.h"
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include <iostream>
#include "Macros.h"
#include "InputManager.h"
#include "Util.h"

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
double maxDistance, string sprite, int x, int y): Component(associated) {
    (void)maxDistance;    (void)speed;    (void)damage;
    this->target = Vec2(x,y);
    cout << "BULLET ON" << endl;
    this->distanceLeft = 1000000;
    this->mySprite = new Sprite(this->associated, sprite.c_str());
    this->associated.AddComponent(
        this->mySprite
    );
    this->associated.AddComponent(this);
    cout << "target : " << target << endl;
    myAbort(101);
    this->associated.box.SetXY(target);   // colocar na origem o bullet. Ver se vai em direcao ao CLICK
    // myAbort(12);
    this->speed = Vec2(1,0);    // base speed
    this->speed.rotate(angle);

    this->speed = this->speed.unitary() * speed;

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
/*     if(this->distanceLeft > 0) {
 */        /* this->UpdatePos(); */
        
        // this->distanceLeft -= this->speed.abs();
    Bullet::UpdatePos(dt);
        // this->associated.RequestDelete();
/*     }
    else {
        this->associated.RequestDelete();
        myAbort(11);

        // this->distanceLeft -= (speed*;
    }
 */    // cout << "BULLET UPDATE << " << this << endl;
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