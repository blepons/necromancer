#include "rest_action.hpp"
#include "action.hpp"
#include "entity_action.hpp"
#include "hero.hpp"
#include "stage.hpp"

namespace rln {

RestAction::RestAction(Game* game, Point pos, Entity* entity)
    : EntityAction(game, pos, entity) {}

ActionResult RestAction::perform() {
    if (auto hero = dynamic_cast<Hero*>(entity()); hero != nullptr) {
        hero->increase_health(3);
        hero->gain_mana(15);
    } else if (game()->stage()->visible_to_hero(entity())) {
        entity()->increase_health(2);
    }
    return ActionResult::succeed();
}

}  // namespace rln
