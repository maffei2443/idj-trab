#include "GameObject.h"
#include "Rect.h"
#include "Macros.h"
#include <cstdio>
GameObject :: GameObject() : isDead(false), box() {}

GameObject :: ~GameObject() {
    printf("GO deletado...\n");
    // Liberando em ordem reversa À que foi alocado
    for(int i = this->components.size(); i > -1 ;i--) {
        printf("%d\n",this->components[i] == nullptr);
        fflush(stdout);
        // TODO : FOUND BUG : segfault if call delete
        // delete this->components[i];
        // this->components[i]->~Component();
        // printf("Destruiuuuuuuuuu\n");
    }

    // this->components.clear();
    // printf("CLEARED\n");
    fflush(stdout);

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
    // BUG POSSIVEL
    // this->components.push_back(cpt);
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

// DUVIDA : O QUE ESTAH SENDO PEDIDO ?
Component* GameObject :: GetComponent(std::string type) {
    for(auto* comp : this->components) {
        if(comp->Is(type))
            return comp;
    }
    LOG("Objeto não exixtente\n");
    // LOG("Método incompleto!!! Terminna logo  isso..\n");
    return nullptr;
}