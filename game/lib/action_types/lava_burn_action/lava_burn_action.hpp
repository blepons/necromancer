#pragma once

#include "action.hpp"

namespace rln {

class LavaBurnAction : public Action {
public:
    LavaBurnAction(Game* game, Point pos);

    ActionResult perform() override;
};

}  // namespace rln
