#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>

#include "Rect.h"
#include "Component.h"
using std::vector;
using std::string;
// Logic grouper of the 
class GameObject {
private:
  static const string type;
  vector <Component*> components;
  bool isDead;
  // ideia: permitir restaurar p/ tamanho original
  // caso necessário. Basta armazenar w e h originais
  Vec2 originalDimension;
  Vec2 speed;
  double currentDt;
public:
  GameObject();
  ~GameObject();

  void Update(double dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(Component* cpt);
  void RemoveComponent(Component* cpt);
  Vec2 GetOriginalDim();
  Component* GetComponent(string type);
  
  Rect box;
  // t5
  void Start();
  void NotifyCollision(GameObject &other);
  bool started = false;
  // 
  /* Agora adicione + angleDeg : double ao GameObject
    e inicialize-o com 0 no construtor. */
  double angleDeg = 0;
  const inline string GetType() const {
    return this->type;
  }
  // Na verdade,
  const Vec2 GetSpeed() {
    return this->speed;
  }
  const Vec2 GetSpeedWithDt() {
    return this->speed * this->currentDt;
  }
  const void SetSpeed(Vec2 speed) {
    this->speed = speed;
  }
};

#endif