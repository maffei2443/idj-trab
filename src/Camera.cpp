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
const float Camera::SPEED = 0.7;

float Camera::GetHorizontalSpeed() {
    return (
        inputManager->IsKeyDown(SDLK_RIGHT) + inputManager->IsKeyDown('d')  // right speed
        - inputManager->IsKeyDown(SDLK_LEFT) - inputManager->IsKeyDown('a')  // left speed
    );
}

float Camera::GetVerticalSpeed() {
    return (
        inputManager->IsKeyDown(SDLK_UP) + inputManager->IsKeyDown('w')  // right speed
        - inputManager->IsKeyDown(SDLK_DOWN) - inputManager->IsKeyDown('s')  // left speed
    );
}


void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    // (void)dt;  // TODO: usar esse dt
    /* Se a câmera tiver um foco, faremos com que ele fique 
    centralizado na tela. Nesse caso, o movimento independe de dt,
    depende apenas do tamanho da tela. */
    if (Camera::focus) {
        // Centralizar objeto focado
        Camera::pos.x = Camera::focus->box.x; // POSSIVEL BUG
        Camera::pos.y = Camera::focus->box.y; // POSSIVEL BUG
        printf("CAMERA::UPDATE\n");
    }
    else {
        /* Se não houver um foco, devemos responder ao input:
        SETAMOS A VELOCIDADE DA CÂMERA DE ACORDO COM DT E COM AS
        TECLAS PRESSIONADAS, E SOMAMOS À POSIÇÃO */

        float horizontalSpeed =  Camera::SPEED*Camera::GetHorizontalSpeed();
        float verticalSpeed =  -Camera::SPEED*Camera::GetVerticalSpeed();   // SDL crece pra baixo
        Camera::speed = Vec2(horizontalSpeed/* *dt */, verticalSpeed/* *dt */);
        Camera::pos = Camera::pos + (Camera::speed*dt);
    }
    
}
