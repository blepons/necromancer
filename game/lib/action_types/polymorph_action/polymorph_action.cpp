#include "polymorph_action.hpp"
#include <memory>
#include <string>
#include "entity.hpp"
#include "stage.hpp"

namespace rln {

PolymorphAction::PolymorphAction(Game* game,
                                 Point pos,
                                 std::shared_ptr<Entity> entity,
                                 std::string new_undead_type)
    : EntityAction(game, pos, entity),
      new_undead_type_(std::move(new_undead_type)) {}

ActionResult PolymorphAction::perform() {
    if (auto undead = std::dynamic_pointer_cast<Undead>(
            game()->stage()->entity_at(pos()));
        undead != nullptr) {
        int init_hp =
            undead->health() /
            game()->undead_registry().multiplier(undead->undead_type());
        int init_max_hp =
            undead->max_health() /
            game()->undead_registry().multiplier(undead->undead_type());
        int new_hp =
            init_hp * game()->undead_registry().multiplier(new_undead_type_);
        int new_max_hp = init_max_hp *
                         game()->undead_registry().multiplier(new_undead_type_);

        undead->health(new_hp);
        undead->max_health(new_max_hp);
        undead->undead_type(new_undead_type_);
        return ActionResult::succeed();
    }
    return ActionResult::fail();
}

}  // namespace rln
