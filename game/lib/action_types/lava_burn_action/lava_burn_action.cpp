#include "lava_burn_action.hpp"
#include "stage.hpp"

namespace rln {

LavaBurnAction::LavaBurnAction(Game* game, Point pos) : Action(game, pos) {}

ActionResult LavaBurnAction::perform() {
    auto entity = game()->stage()->entity_at(pos());
    if (entity != nullptr) {
        entity->take_damage(shared_from_this(), 10, nullptr);
    }
    return ActionResult::succeed();
}

}  // namespace rln
