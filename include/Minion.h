#ifndef MINION_H
#define MINION_H

#include "GameObject.h"
#include "Vec2.h"
#include <memory>

#include <iostream>
#include "Sprite.h"
using std::cout;
using std::endl;

using std::weak_ptr;
using std::string;

class Minion : public Component {
private:
  double arc;
  weak_ptr<GameObject> alienCenter;
  Vec2 innerPos;  // de raio arbitrario, em relacao aa origem
  // TESTE FUNCIONA
  // std::weak_ptr<GameObject> alienCenter;
  Sprite* mySprite;
public:
    const string type = string("Minion");
    Minion(GameObject&, weak_ptr<GameObject>, double, Vec2 initPos=Vec2(rand()%360, 0));
    ~Minion();
    // herda de Component
    void Update(double);
    void Render();
    bool Is(string);
    void Shoot(Vec2);
    void Start();
    Rect GetBox();
    void NotifyCollision(GameObject& other);

    const string GetType() const {
      return this->type;
    }
};

#endif