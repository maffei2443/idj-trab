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
    vector <Component*> components;
    bool isDead;
public:
    GameObject();
    ~GameObject();

    void Update(double dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    Rect box;

    // t5
    void Start();
    bool started = false;
};

#endif