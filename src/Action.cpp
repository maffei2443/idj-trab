#include "Action.h"

Action::Action(ActionType actionType, int x, int y) {
    this->type = actionType;
    this->pos = {x, y};
}

