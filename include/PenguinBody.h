#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H
#include "Component.h"
#include "Vec2.h"
#include <queue>
#include <memory>
#include "Action.h"
#include "Click.h"
#include "Sprite.h"
#include "Minion.h"
using std::queue;
using std::vector;
using std::weak_ptr;
using std::shared_ptr;
using std::string;

class PenguinBody : public Component {
private:
    // void UpdatePosAndSpeed(double dt);
    // void UpdatePos(double dt);
    const static string type;
    // void gotoTarget();
    const static int HEALTH_POINTS = 30;
    int hitspoints;
    weak_ptr<GameObject> pcannon;
    // t5
    Vec2 speed = Vec2(0,0);
    double linearSpeed = 0;
    double angle = 0;
    int hp = HEALTH_POINTS;
    shared_ptr<GameObject> associatedSharedPtr;
    Sprite* mySprite;
public:
    
    static PenguinBody* player;
    PenguinBody(GameObject&);
    ~PenguinBody();
    // herda de Component
    void Start();
    void Update(double dt);
    void Render();
    bool Is(string type);
    void NotifyCollision(GameObject& other);
    
    const inline string GetType() const {
        return this->type;
    }
    // t5
    Vec2 GetSpeed() {
        return this->speed;
    }
};

#endif