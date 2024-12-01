#include "rest_action.hpp"
#include <memory>
#include "action.hpp"
#include "entity_action.hpp"
#include "hero.hpp"
#include "stage.hpp"

namespace rln {

RestAction::RestAction(Game* game, Point pos, std::shared_ptr<Entity> entity)
    : EntityAction(game, pos, entity) {}

ActionResult RestAction::perform() {
    if (auto hero = std::dynamic_pointer_cast<Hero>(entity());
        hero != nullptr) {
        hero->increase_health(3);
        hero->gain_mana(15);
    } else {  // TODO: check if it's visible by hostile entities
        entity()->increase_health(2);
    }
    return ActionResult::succeed();
}

}  // namespace rln
