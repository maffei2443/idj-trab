#include "CameraFollower.h"

#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include "Camera.h"
using std::string;
const string CameraFollower::type("CameraFollower");
// Class responsible for the game logic.

CameraFollower::CameraFollower(GameObject& associated) : Component(associated)
    {
}

void CameraFollower::Update(double dt) {
    this->associated.box.x = Camera::pos.x;
    this->associated.box.y = Camera::pos.y;
}
void CameraFollower::Render() {

}
bool CameraFollower::Is(string type) {
    return this->type == type;
}
