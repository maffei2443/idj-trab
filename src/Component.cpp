#include "Component.h"
#include "GameObject.h"
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;
// Component::Component() {

// }

const string Component::type("Component");

Component::~Component() {
    cout << "COMPONENT-" << this << " [" << this->type << "] DESTRUCTOR" << endl;
}

Component::Component(GameObject& associated) : associated(associated) {
    
}