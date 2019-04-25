#ifndef FACE_H
#define FACE_H
#include "Component.h"

class Face : public Component {
private:
    const static int HEALTH_POINTS = 30;
    int hitspoints;
public:
    const std::string type = std::string("Face");
    Face(GameObject& associated);
    void Damage(int damage);
    // herda de Component
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    const inline std::string GetType(){
        return this->type;
    }
    // t5
    bool started = false;
    void Start();
};

#endif