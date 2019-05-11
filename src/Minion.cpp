#include "Minion.h"
#include "GameObject.h"
#include "Vec2.h"
#include <memory>
#include <iostream>
using std::weak_ptr;
using std::string;
using std::cout;
using std::endl;
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"

Minion::Minion (GameObject& associated, weak_ptr<GameObject> alienCenter,
    double arcOffsetDeg, Vec2 initPos) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    this->mySprite = new Sprite(this->associated, "assets/img/minion.png");
    initPos.rotate(arcOffsetDeg);
    this->innerPos = initPos;
    cout << "OFF_SET DEGREE : " << arcOffsetDeg << endl;

    this->associated.box.SetXYWH(
        this->alienCenter.box.center.x, 
        this->alienCenter.box.center.y, 
        mySprite->GetWidth(), 
        mySprite->GetHeight()
    ) ;
    this->associated.box.AddX( arcOffsetDeg ); 
/*     cout << "CENTER OF DAMMIT ALIEN : " << this->alienCenter.box.center << endl;
    cout << "CENTER OF FUCKING MINION : " << this->associated.box.center << endl;
 */ 
    this->associated.AddComponent(this);
}

Minion::~Minion () {
    printf("MINION OF %p DYINGGGGGGGGGGGGGGG\n", this);
}

// herda de Component
void Minion::Update(double dt) {
    (void)dt;
    innerPos.rotate(0.07);
    Vec2 newPos =  innerPos 
                   + this->alienCenter.box.center 
                //    - Vec2(this->alienCenter.box.w/2, this->alienCenter.box.h/2) 
                   ;
    this->associated.box.SetCenter(newPos);
    // cout << "??? : " << this->associated.box << endl;
    // OK funcionando
}

void Minion::Render(){ 
    
}

bool Minion::Is(string type){ 
    return type == "Minion";
}


// t5
void Minion::Shoot(Vec2 direction) {
    GameObject* GO_of_bullet = new GameObject;
    cout << "Old direction : " << direction << endl;
    cout << "Alien.box.Center => " << this->associated.box.center << endl;
    cout << "Alien.associated.box => " << this->associated.box << endl;
    // myAbort(14);
    direction = direction - Vec2(this->associated.box);

    Vec2 vecNormalized = direction.unitary();
    Vec2 myPos = Vec2(this->associated.box);
    double angle = RAD2DEG * atan2(vecNormalized.y, vecNormalized.x) ;
    // cout << "Minion.associated.box == " << this->associated.box << endl;
    int damage = 0;
    double speed = 0.2;
    double maxDistance = 100000;
    new Bullet(*GO_of_bullet, angle, speed, damage, maxDistance,
        "assets/img/minionbullet1.png", this->associated.box.x, this->associated.box.y);
    // cout << "ADDED BULLET\n";
    Game::GetInstance().GetState().AddObject(GO_of_bullet);

}

void Minion::Start() {
    this->started = true;
}

Rect Minion::GetBox() {
    return this->associated.box;
}