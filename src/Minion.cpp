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
    double arcOffsetDeg, Vec2 initPos=Vec2(rand()%360, 0)) : arc(arcOffsetDeg),Component(associated), alienCenter(*alienCenter.lock().get()) {
    this->mySprite = new Sprite(this->associated, "assets/img/minion.png");
    // this->associated.box.SetCenter(this->alienCenter.box.center);
    this->associated.box.SetXYWH(this->alienCenter.box.center.x, this->alienCenter.box.center.y , mySprite->GetWidth(), mySprite->GetHeight()  ) ;    
    cout << "CENTER OF DAMMIT ALIEN : " << this->alienCenter.box.center;
    cout << "CENTER OF FUCKING MINION : " << this->associated.box.center;
    cout << "BOX OF FUCKING MINION : " << this->associated.box;
    // myAbort(1006);
    this->associated.AddComponent(this);
    this->innerPos = initPos;
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
    // cout << "innerPos : " << innerPos << endl;
    this->associated.box.SetCenter(newPos);
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
    cout << "Alin.Center => " << this->associated.box.center;
    direction = direction - Vec2(this->associated.box);

    cout << "New direction : " << direction << endl;

    Vec2 vecNormalized = direction.unitary();
    Vec2 myPos = Vec2(this->associated.box);
    cout << "this->associated.box ==> " << this->associated.box << endl;
    cout << "MyPos : " << myPos << endl;
    // abort();
    double angle = RAD2DEG * atan2(vecNormalized.y, vecNormalized.x) ;
    new Bullet(*GO_of_bullet, angle, .20, 1, 0, "assets/img/minionbullet1.png");
    // cout << "ADDED BULLET\n";
    Game::GetInstance().GetState().AddObject(GO_of_bullet);

}

void Minion::Start() {

}