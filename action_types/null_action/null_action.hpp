#pragma once

#include "action.hpp"

namespace rln {

class NullAction : public Action {
public:
    NullAction();

    ActionResult perform() override;
};

}
