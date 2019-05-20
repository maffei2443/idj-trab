#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include "GameObject.h"
#include "Music.h"
#include "Component.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
using std::string;
// Class responsible for the game logic.
class CameraFollower : public Component {
  private:
    static const string type;
  public:

    CameraFollower(GameObject&);
    void Update(double dt);
    void Render();
    bool Is(string);
    const string GetType() const {
        return this->type;
    }
    void Start();
    void NotifyCollision(GameObject& other);
};

#endif