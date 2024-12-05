#pragma once

#include "action.hpp"

namespace rln {

class NextFloorAction : public Action {
public:
    NextFloorAction(Game* game);

    ActionResult perform() override;
};

}
