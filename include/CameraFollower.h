#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include "GameObject.h"
#include "Music.h"
#include "Component.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
// Class responsible for the game logic.
class CameraFollower : public Component {

  public:
    const std::string type;
    const std::string GetType();

    CameraFollower(GameObject&);
    void Update(float dt);
    void Render();
    bool Is(std::string);
};

#endif