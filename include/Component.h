#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
// forward decl @cristianokrugbrust

class GameObject;  // como nao usa o obj, permite forw. decl

#include <string>
using std::string;
// Add logic to the game through inheritance
class Component{
protected:
    bool started = false;
    GameObject& associated; // where I am
    static const string type;
public:
    // Component(); // COMPILADOR RECLAMOU QUE tal classe nao tinha
    // // construtor padrao

    Component(GameObject& associated);
    virtual ~Component();

    void virtual Update(double dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;
    const string virtual GetType() const = 0;
    Component* GetAddr() { return this;}
    // t5
    /* E, por último, em Component, adicione o método + Start() : virtual
void e deixe o corpo vazio em sua implementação */
    void virtual Start() = 0;
};

#endif