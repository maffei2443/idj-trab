#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Macros.h"
#include "Sprite.h"
#include <memory>
#include "InputManager.h"
#include <cmath>  // atan2
#include "Camera.h"
#include "Vec2.h"
#include "Bullet.h"
#include <iostream>
#include "Collider.h"

using std::cout;
using std::endl;

#define atan2Vec(VEC) atan2( (VEC).y, (VEC).x )
using std::weak_ptr;
const string PenguinCannon::type("PenguinCannon");
static InputManager& inputManager = InputManager::GetInstance();


PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) :
  Component(associated), pbody(penguinBody){
    this->angle = 0.0;
    this->mySprite = new Sprite(this->associated, "assets/img/cubngun.png");
    this->associated.AddComponent(this);
    new Collider(this->associated);
}

PenguinCannon::~PenguinCannon(){
  cout << "[" << this->GetType() << "] DESTRUCTOR" << endl;
}

void PenguinCannon::Start() {
  this->started = true;
}
void PenguinCannon::Update(double dt) {
  (void)dt;
  GameObject* penguinBodyGO = pbody.lock().get();
  // verificar se o PenguinBody ainda existe.
  if(not penguinBodyGO)
    this->associated.RequestDelete();
  else {
    // fazer com que o centro da box dele seja igual ao centro da box do corpo
    this->associated.box.SetCenter(
      penguinBodyGO->box.GetCenter()
    );
    Vec2 target(inputManager.GetMouseX(), inputManager.GetMouseY());
    Vec2 diffVec( target - this->associated.box.GetCenter() );
    // ver angulo entre target e o centro da box, para atirar
    // Para saber o ângulo, use o
    // centro da box, que, como veremos em seguida, coincidirá com o eixo do
    // canhão, e forme uma reta. O canhão deve ter o mesmo ângulo dessa reta.
    this->angle = atan2Vec(diffVec) * RAD2DEG ;
    this->mySprite->Rotate( this->angle );
    // Não se esqueça de considerar a posição da câmera.
    // POSSIVEL BUG
    this->associated.box.AddXY(Camera::pos * dt);
  }
  myAbort(54321);
}
void PenguinCannon::Render() {
  // vazio para PenguinCannon e PenguinBody
}
bool PenguinCannon::Is(string type) {
  return type == this->type;
}
void PenguinCannon::Shoot(){
  myAbort(1);
  /* Esta função é similar à de mesmo nome em Minion, com apenas duas
diferenças. A primeira é que não precisamos de um ponto para calcular o
ângulo do tiro: já fizemos isso em Update para obter o ângulo do canhão. A
segunda diferença é que, como queremos que o tiro saia da ponta do canhão,
precisamos estabelecer uma distância do centro dos PenguinCannon onde será
colocada a Bullet */
  Vec2 farFromCenter(100, 0);
}

