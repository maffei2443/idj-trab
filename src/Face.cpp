#include "Face.h"
#include <unistd.h>
Face :: Face(GameObject& associated):
            associated(associated),
            hitspoints(Face::HEALTH_POINTS){}

void Face ::  Damage(int damage) {
    this->hitspoints -= damage;
    if(hitspoints < 1) {    // TODO: otimização (usando manipulação e bits)
        this->associated->RequestDelete();
        Component* cmptPtr = this->associated->GetComponent("Sound");
        Sound * sndPtr = (Sound*) cmptPtr;

        if(sndPtr){   
            sndPtr->Play();
            sleep(1);   // TODO: melhorar isso.
        }
    }
}
// Face ::  herda de Componen {

}
void Face ::  Update(float dt) {

}
void Face ::  Render() {
    // Itentionally left empty.
}
bool Face :: Is(std::string type) {
    return type == "Face";
}