#pragma once

#include "action.hpp"

namespace rln {

// TODO: should it be removed?
class NullAction : public Action {
public:
    NullAction();

    ActionResult perform() override;
};

}  // namespace rln
