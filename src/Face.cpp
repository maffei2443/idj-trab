#include <unistd.h>
#include "Face.h"
#include "Sound.h"
#include "Component.h"
#include "Macros.h"
#include "Camera.h"
#include "InputManager.h"
#include "GameObject.h"
const string Face::type("Face");
static InputManager& inputManager = InputManager::GetInstance();

Face::Face(GameObject& associated): 
    Component(associated),
    hitspoints(Face::HEALTH_POINTS){
}

// BUG POSSIVEL
void Face:: Damage(int damage) {
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
// Face:: herda de Componen {


void Face:: Update(double dt) {
    (void)dt;
    // Atualizar posição de acordo com a câmera
/*  Segundo, em Update (fiz), quando for checar
    se a Face foi clicada, compense o deslocamento da câmera
    nas coordenadas do mouse [???] - O InputManager nos dá 
    as coordenadas da tela, não do mundo
 */
	// if( inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
	// 	double mouseX = inputManager.GetMouseX();
	// 	double mouseY = inputManager.GetMouseY();
    //     // GameObject* go = (GameObject*) objectArray[i].get();
    //     if(this->associated.box.Contains( {mouseX, mouseY} ) ) {
    //         this->Damage(/* std::rand() % 10 + 10 */20);
    //         printf("Dano! %d\n", this->hitspoints);
    //     }
	// }
    this->associated.box.AddXY(Camera::speed);

}
void Face:: Render() {
    // Itentionally left empty.
    // Primeiro, faça A RENDERIZAÇÃO deles levar em
    // consideração a posição da câmera. (FIZ O UPDATE)

}
bool Face::Is(std::string type) {
    return type == "Face";
}

// t5
void Face::Start() {
    this->started = true;
}