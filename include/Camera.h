#ifndef CAMERA_H
#define CAMERA_H

#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>

// Class responsible for the game logic.
class Camera {
  private:
    static GameObject * focus;
    static int GetHorizontalSpeed();
    static int GetVerticalSpeed();
  public:
    static Vec2 pos;
    static Vec2 speed;
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

    // auxiliar para a velocidade; no momento, camera
    // nao muda a velocidade
    static const int SPEED;

};

#endif