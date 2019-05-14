#include "CameraFollower.h"

#include "GameObject.h"
#include "Music.h"
#include <vector>
#include <memory>  // unique_ptr
#include <string>
#include <iostream>
using std::cout;
using std::endl;

#include "Camera.h"
using std::string;
const string CameraFollower::type("CameraFollower");
// Class responsible for the game logic.

CameraFollower::CameraFollower(GameObject& associated) : Component(associated)
    {
        this->associated.AddComponent(this);
}

void CameraFollower::Update(double dt) {
    // this->associated.box.SetXY({Camera::pos*dt});
    this->associated.box.AddXY(Camera::speed * dt);
    // cout << "UPDATE CAMERA FOLLOWER" << endl;
}
void CameraFollower::Render() {

}
bool CameraFollower::Is(string type) {
    return this->type == type;
}
void CameraFollower::Start() {
    this->started = true;
}