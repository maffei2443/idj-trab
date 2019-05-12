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
    this->associated.box.SetXY(Camera::pos);
}
void CameraFollower::Render() {

}
bool CameraFollower::Is(string type) {
    return this->type == type;
}
void CameraFollower::Start() {
    this->started = true;
}