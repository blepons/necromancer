#include "change_state_action.hpp"
#include <memory>
#include <utility>
#include "mob.hpp"

namespace rln {

ChangeStateAction::ChangeStateAction(Game* game,
                                     Point pos,
                                     std::shared_ptr<Entity> entity,
                                     std::unique_ptr<MobState>&& state)
    : EntityAction(game, pos, entity), state_(std::move(state)) {}

ActionResult ChangeStateAction::perform() {
    auto mob = std::static_pointer_cast<Mob>(entity());
    mob->change_state(std::move(state_));
    return ActionResult::alternate(mob->state().action(game()));
}

}  // namespace rln
