#include "Action.h"

Action::Action(ActionType actionType, float x, float y) {
    this->type = actionType;
    this->pos = {x, y};
}

