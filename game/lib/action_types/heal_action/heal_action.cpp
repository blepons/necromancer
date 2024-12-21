#include "heal_action.hpp"
#include <memory>
#include "entity.hpp"

namespace rln {

HealAction::HealAction(Game* game,
                       Point pos,
                       std::shared_ptr<Entity> entity,
                       int amount)
    : EntityAction(game, pos, entity), amount_(amount) {}

ActionResult HealAction::perform() {
    if (entity()->health() != entity()->max_health()) {
        entity()->increase_health(amount_);
        add_event(Event(Event::EventType::HEAL, entity(), pos()));
    }
    return ActionResult::succeed();
}

}  // namespace rln
