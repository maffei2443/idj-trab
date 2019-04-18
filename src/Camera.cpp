#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Vec2.h"

GameObject* Camera::focus;
// posicao do observador [camera] hipotehtico (centralizado, a pincihpio)
Vec2 Camera::pos(0,0);
// observador [camera] parado
Vec2 Camera::speed(0,0);
InputManager* inputManager = &InputManager::GetInstance();
const int Camera::SPEED = 15;

int Camera::GetHorizontalSpeed() {
    return (
        inputManager->IsKeyDown(SDLK_RIGHT) + inputManager->IsKeyDown('d')  // right speed
        - inputManager->IsKeyDown(SDLK_LEFT) - inputManager->IsKeyDown('a')  // left speed
    );
}

int Camera::GetVerticalSpeed() {
    return (
        inputManager->IsKeyDown(SDLK_UP) + inputManager->IsKeyDown('w')  // right speed
        - inputManager->IsKeyDown(SDLK_DOWN) - inputManager->IsKeyDown('s')  // left speed
    );
}


void Camera :: Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera :: Unfollow() {
    focus = nullptr;
}

void Camera :: Update(float dt) {
    (void)dt;  // TODO: usar esse dt
    /* Se a câmera tiver um foco, faremos com que ele fique 
    centralizado na tela. Nesse caso, o movimento independe de dt,
    depende apenas do tamanho da tela. */
    if (Camera::focus) {
        // Centralizar objeto focado
        Camera::pos.x = Camera::focus->box.x; // POSSIVEL BUG
        Camera::pos.y = Camera::focus->box.y; // POSSIVEL BUG
    }
    else {
        /* Se não houver um foco, devemos responder ao input:
        SETAMOS A VELOCIDADE DA CÂMERA DE ACORDO COM DT E COM AS
        TECLAS PRESSIONADAS, E SOMAMOS À POSIÇÃO */

        // TODO: pegar, do inputManager, quais (wasd) tecla está pressionada.
        // e setar velocidade conforme tais fatos.
        int horizontalSpeed =  -Camera::SPEED*Camera::GetHorizontalSpeed();
        int verticalSpeed =  Camera::SPEED*Camera::GetVerticalSpeed();
        Camera::speed = Vec2(horizontalSpeed, verticalSpeed);
        Camera::pos = Camera::pos + Camera::speed;

    }
    
}
