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
    static double GetHorizontalSpeed();
    static double GetVerticalSpeed();
  public:
    static Vec2 pos;
    static Vec2 speed;
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(double dt);

    // auxiliar para a velocidade; no momento, camera
    // nao muda a velocidade
    static const double SPEED;

};

#endif