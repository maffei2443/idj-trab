#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H
#include <memory>
#include "Component.h"
#include "Vec2.h"
#include "Action.h"
#include "Sprite.h"
#include "PenguinBody.h"
#include "Timer.h"
#define BIG_DIST 1e12
using std::queue;
using std::vector;
using std::weak_ptr;
using std::string;
class PenguinCannon : public Component {
private:
    // void UpdatePosAndSpeed(double dt);
    // void UpdatePos(double dt);
    const static string type;
    // void gotoTarget();
    const static int HEALTH_POINTS = 30;
    int hitspoints;
    // t5
    Vec2 speed = Vec2(0,0);
    double angle = 0;
    weak_ptr<GameObject> pbody;
    Timer cooldown;

public:
    
    PenguinCannon(GameObject&, weak_ptr<GameObject> penguinBody);
    ~PenguinCannon();
    // herda de Component
    void Start();
    void Update(double dt);
    void Render();
    bool Is(string type);
    const inline string GetType() const {
        return this->type;
    }
    void Shoot();
};

#endif