#include "do_nothing_action.hpp"
#include <memory>

namespace rln {

DoNothingAction::DoNothingAction(Game* game,
                                 Point pos,
                                 std::shared_ptr<Entity> entity)
    : EntityAction(game, pos, entity) {}

ActionResult DoNothingAction::perform() {
    return ActionResult::succeed();
}

}  // namespace rln
