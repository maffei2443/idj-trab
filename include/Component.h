#ifndef COMPONENT_H
#define COMPONENT_H

// forward decl @cristianokrugbrust

class GameObject;  // como nao usa o obj, permite forw. decl

#include <string>
// Add logic to the game through inheritance
class Component{
protected:
    GameObject& associated; // where I am
public:
    Component(); // COMPILADOR RECLAMOU QUE tal classe nao tinha
    // // construtor padrao

    Component(GameObject& associated);
    virtual ~Component();

    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(std::string type) = 0;
};

#endif