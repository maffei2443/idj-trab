#include "GameObject.h"
#include "Rect.h"
#include "Macros.h"
#include <cstdio>
GameObject :: GameObject() : isDead(false), box() {}

GameObject :: ~GameObject() {
    this->components.clear();
}

void GameObject :: Update(float dt) {
    for(auto& comp : this->components) {
        comp->Update(dt);
    }
}
void GameObject :: Render() {
    for(auto& comp : this->components) {
        comp->Render();
    }
}

bool GameObject :: IsDead() {
    return this->isDead;
}
void GameObject :: RequestDelete() {
    this->isDead = true;
}
void GameObject :: AddComponent(Component* cpt) {
    this->components.emplace_back(cpt);
}

void GameObject :: RemoveComponent(Component * cpt) {
    std::size_t len = this->components.size();
    for(std::size_t i = 0; i < len; i++ ) {
        if (cpt != this->components[i]) continue;
        this->components.erase(this->components.begin() + i);
        break;
    }
}

Component* GameObject :: GetComponent(std::string type) {
    for(auto* comp : this->components) {
        if(comp->Is(type))
            return comp;
    }
    LOG("Objeto não exixtente\n");
    return nullptr;
}