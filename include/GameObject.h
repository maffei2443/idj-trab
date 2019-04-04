#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Rect.h"
#include "Component.h"
#include "GameObject.h"
// Logic grouper of the 
class GameObject {
private:
    std::vector <Component*> components;
    bool isDead;
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);
    Rect box;

};

#endif