#include "next_floor_action.hpp"

namespace rln {

NextFloorAction::NextFloorAction(Game* game)
    : Action(game, {0, 0}) {}

ActionResult NextFloorAction::perform() {
    game()->next_floor();
    return ActionResult::succeed();
}

}
