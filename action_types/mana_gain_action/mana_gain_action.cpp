#include "mana_gain_action.hpp"
#include <memory>
#include "hero.hpp"

namespace rln {

ManaGainAction::ManaGainAction(Game* game,
                               Point pos,
                               std::shared_ptr<Hero> hero,
                               int amount)
    : EntityAction(game, pos, std::static_pointer_cast<Entity>(hero)),
      amount_(amount) {}

ActionResult ManaGainAction::perform() {
    auto hero = std::static_pointer_cast<Hero>(entity());
    if (hero->mana() != hero->max_mana()) {
        hero->gain_mana(amount_);
    }
    return ActionResult::succeed();
}

}  // namespace rln
