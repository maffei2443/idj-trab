#include "Action.h"

Action::Action(ActionType actionType, double x, double y) {
    this->type = actionType;
    this->pos = {x, y};
}

