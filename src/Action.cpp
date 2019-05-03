#include "Action.h"

Action::Action(ActionType actionType, int x, int y) {
    this->type = actionType;
    this->pos = new Vec2(x, y);
}
Action::~Action() {
    delete this->pos;
}
