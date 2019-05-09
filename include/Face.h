#ifndef FACE_H
#define FACE_H
#include "Component.h"
using std::string;

class Face : public Component {
private:
    const static string type;
    const static int HEALTH_POINTS = 30;
    int hitspoints;
public:
    
    Face(GameObject& associated);
    void Damage(int damage);
    // herda de Component
    void Update(double dt);
    void Render();
    bool Is(string type);
    const inline string GetType() const {
        return this->type;
    }
    // t5
    bool started = false;
    void Start();
};

#endif