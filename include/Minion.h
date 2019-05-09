#ifndef MINION_H
#define MINION_H

#include "GameObject.h"
#include "Vec2.h"
#include <memory>

#include <iostream>
using std::cout;
using std::endl;

using std::weak_ptr;
using std::string;

class Minion : public Component {
private:
  double arc;
  GameObject& alienCenter;  
  // TESTE FUNCIONA
  // std::weak_ptr<GameObject> alienCenter;
public:
    const string type = string("Minion");
    Minion(GameObject&, weak_ptr<GameObject>, double, const Vec2& vec=Vec2(200,0));
    ~Minion();
    // herda de Component
    void Update(double);
    void Render();
    bool Is(string);

    const string GetType() const {
      return this->type;
    }
    // t5
    void Shoot(Vec2);
    void Start();
};

#endif