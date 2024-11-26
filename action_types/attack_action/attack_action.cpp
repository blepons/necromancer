#include "attack_action.hpp"
#include <memory>
#include "entity.hpp"
#include "entity_action.hpp"

namespace rln {

AttackAction::AttackAction(std::shared_ptr<Entity> attacker,
                           std::shared_ptr<Entity> target,
                           Game* game,
                           Point pos)
    : EntityAction(game, pos, attacker), target_(target) {}

ActionResult AttackAction::perform() {
    entity()->attack(target_);
    return ActionResult::succeed();
}

}  // namespace rln
