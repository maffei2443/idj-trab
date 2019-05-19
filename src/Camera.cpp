#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Game.h"
#include "Util.h"

/*  */
#include <iostream>
using std::cout;
using std::endl;

/*  */
GameObject* Camera::focus;
// posicao do observador [camera] hipotehtico (centralizado, a pincihpio)
Vec2 Camera::pos(0,0);
// observador [camera] parado
Vec2 Camera::speed(0,0);
InputManager* inputManager = &InputManager::GetInstance();
const double Camera::SPEED = 0.7;

double Camera::GetHorizontalSpeed() {
    return (
        inputManager->IsKeyDown(SDLK_RIGHT)  // right speed
        - inputManager->IsKeyDown(SDLK_LEFT)  // left speed
    );
}

double Camera::GetVerticalSpeed() {
    return (
        inputManager->IsKeyDown(SDLK_UP)  // right speed
        - inputManager->IsKeyDown(SDLK_DOWN)  // left speed
    );
}


void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(double dt) {
    // (void)dt;  // TODO: usar esse dt
    /* Se a câmera tiver um foco, faremos com que ele fique 
    centralizado na tela. Nesse caso, o movimento independe de dt,
    depende apenas do tamanho da tela. */
    if (Camera::focus) {
        // Centralizar objeto focado
        Game& game = Game::GetInstance();
/*         Camera::pos = 
            Vec2(game.GetWidth()/2, game.GetHeight()/2)
                -
            Camera::focus->box
        ;
 */       
/*       Camera::pos = 
        Camera::focus->box * (-1)
      ; */
/*       Camera::pos = 
        (Camera::focus->box - Vec2(game.GetWidth()/2, 0))*(-1)
      ;
 */   
      // Camera::speed = {0.01, 0};
      // Camera::pos = Camera::pos + (Camera::speed);

      Camera::speed.x = Camera::focus->GetSpeed().x;       
      Camera::speed.y = Camera::focus->GetSpeed().y;       
      
      PRINT(Camera::pos);
    }
    else {
        /* Se não houver um foco, devemos responder ao input:
        SETAMOS A VELOCIDADE DA CÂMERA DE ACORDO COM DT E COM AS
        TECLAS PRESSIONADAS, E SOMAMOS À POSIÇÃO */

        // TODO: pegar, do inputManager, quais (wasd) tecla está pressionada.
        // e setar velocidade conforme tais fatos.
        double horizontalSpeed =  -Camera::SPEED*Camera::GetHorizontalSpeed();
        double verticalSpeed =  Camera::SPEED*Camera::GetVerticalSpeed();
        Camera::speed = Vec2(horizontalSpeed, verticalSpeed);
        Camera::pos = Camera::pos + (Camera::speed*dt);
    }
    
}
