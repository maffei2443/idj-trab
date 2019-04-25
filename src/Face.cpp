#include <unistd.h>
#include "Face.h"
#include "Sound.h"
#include "Component.h"
#include "Macros.h"

Face :: Face(GameObject& associated): 
    Component(associated),
    hitspoints(Face::HEALTH_POINTS){
}

// BUG POSSIVEL
void Face ::  Damage(int damage) {
    // throw 67;
    this->hitspoints -= damage;
    if(hitspoints < 1) {    // TODO: otimização (usando manipulação e bits)
        this->associated.RequestDelete();
        Component* cmptPtr = this->associated.GetComponent("Sound");
        Sound * sndPtr = (Sound*) cmptPtr;

        if(sndPtr){
            sndPtr->Play(1);
        }
        else
            LOG(("The face doesn't have SOUND!\n"))
    }
}
// Face ::  herda de Componen {


void Face ::  Update(float dt) {
    (void)dt;
}
void Face ::  Render() {
    // Itentionally left empty.
}
bool Face :: Is(std::string type) {
    return type == "Face";
}