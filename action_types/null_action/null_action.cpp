#include "null_action.hpp"
#include "action.hpp"

namespace rln {

NullAction::NullAction() : Action(nullptr, {0, 0}) {}

ActionResult NullAction::perform() {
    return ActionResult::succeed();
}

}  // namespace rln
