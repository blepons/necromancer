#include "disappear_action.hpp"
#include <memory>
#include "stage.hpp"

namespace rln {

DisappearAction::DisappearAction(Game* game,
                                 Point pos,
                                 std::shared_ptr<Entity> entity)
    : EntityAction(game, pos, entity) {}

ActionResult DisappearAction::perform() {
    game()->stage()->remove_entity(entity());
    return ActionResult::succeed();
}

}  // namespace rln
