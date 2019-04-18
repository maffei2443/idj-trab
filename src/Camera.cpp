#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"

GameObject* Camera::focus;
InputManager* inputManager = &InputManager::GetInstance();


void Camera :: Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera :: Unfollow() {
    focus = nullptr;
}

void Camera :: Update(float dt) {
    /* Se a câmera tiver um foco, faremos com que ele fique 
    centralizado na tela. Nesse caso, o movimento independe de dt,
    depende apenas do tamanho da tela. */
    if (Camera::focus) {
        // Centralizar objeto focado
    }
    else {
        /* Se não houver um foco, devemos responder ao input:
        Setamos a velocidade da câmera de acordo com dt e com as
        teclas pressionadas, e somamos à posição */

        // TODO: pegar, do inputManager, quais (wasd) tecla está pressionada.
        // e setar velocidade conforme tais fatos.

    }
    
}
