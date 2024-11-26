#include "mana_action.hpp"
#include <memory>
#include <utility>
#include "action.hpp"
#include "entity_action.hpp"
#include "hero.hpp"

namespace rln {

ManaAction::ManaAction(std::unique_ptr<EntityAction>&& action, int mana_cost)
    : EntityAction(action->game(), action->pos(), action->entity()),
      wrapped_action_(std::move(action)),
      mana_cost_(mana_cost) {}

ActionResult ManaAction::perform() {
    std::shared_ptr<Hero> hero = std::dynamic_pointer_cast<Hero>(entity());
    if (hero->mana() < mana_cost_) {
        return ActionResult::fail();
    }
    hero->spend_mana(mana_cost_);
    return ActionResult::alternate(std::move(wrapped_action_));
}

}  // namespace rln
