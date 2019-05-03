#ifndef ACTION_H
#define ACTION_H
#include "Vec2.h"

class Action {
    public:
        enum ActionType {MOVE=0, SHOOT};
        ActionType type;
        Vec2 * pos;
        Action(ActionType, int, int);
        Action::~Action();
};


#endif