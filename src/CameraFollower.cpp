#include "CameraFollower.h"

#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include "Camera.h"
// using namespace std;
// Class responsible for the game logic.

const std::string CameraFollower::GetType() {
    return this->type;
}

CameraFollower::CameraFollower(GameObject& associated) : Component(associated)
    , type("CameraFollower") {
}

void CameraFollower::Update(float dt) {
    this->associated.box.x = Camera::pos.x;
    this->associated.box.y = Camera::pos.y;
}
void CameraFollower::Render() {

}
bool CameraFollower::Is(std::string type) {
    return this->type == type;
}
