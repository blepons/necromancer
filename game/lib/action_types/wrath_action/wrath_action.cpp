#include "wrath_action.hpp"
#include <algorithm>
#include <memory>
#include "stage.hpp"

namespace rln {

WrathAction::WrathAction(Game* game,
                         Point pos,
                         std::shared_ptr<Entity> entity,
                         int damage)
    : EntityAction(game, pos, entity), damage_(damage) {}

ActionResult WrathAction::perform() {
    auto& entities = game()->stage()->entities();
    std::for_each(entities.begin(), entities.end(),
                  [action = shared_from_this(), damage = damage_,
                   src = entity(), src_id = entity()->id()](auto& ent) {
                      if (src_id != ent->id()) {
                          ent->take_damage(action, damage, src);
                      }
                  });
    return ActionResult::succeed();
}

}  // namespace rln
