#include "GameObject.h"

GameObject :: GameObject() : isDead(false){}

GameObject :: ~GameObject() {
    // Liberando em ordem reversa À que foi alocado
    for(int i = this->components.size(); i > -1 ;i--) {
        this->components[i]->~Component();
    }
}

void GameObject :: Update(float dt) {
    for(auto comp : this->components) {
        comp->Update(dt);
    }
}

void GameObject :: Render() {
    for(auto comp : this->components) {
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
    this->components.push_back(cpt);
}

void GameObject :: AddComponent(Component* cpt) {
    this->components.push_back(cpt);
}

void GameObject :: RemoveComponent(Component * cpt) {
    std::size_t len = this->components.size();
    for(std::size_t i = 0; i < len; i++ ) {
        if (cpt != this->components[i]) continue;
        this->components.erase(this->components.begin() + i);
        break;
    }
}

Component* GetComponent(std::string type) {
    // 
    throw "Método incompleto!!! Terminna logo  isso..";
}