#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
using std::string;

class Collider : public Component {
private:
    Vec2 scale;
    Vec2 offset;
    const static string type;
public:
    Collider(GameObject&, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    ~Collider();
    void Update(double dt);
    void Render();
    bool Is(string type) {
        return this->type == this->type;
    }
    const inline string GetType() const {
        return this->type;
    }
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    Rect box;
    void Start();
    void NotifyCollision(GameObject& other);
};

#endif