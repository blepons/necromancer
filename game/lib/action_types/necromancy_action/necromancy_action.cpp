#include "necromancy_action.hpp"
#include <memory>
#include <string>
#include "corpse.hpp"
#include "hero.hpp"
#include "stage.hpp"
#include "wander_state.hpp"

namespace rln {

NecromancyAction::NecromancyAction(Game* game,
                                   Point pos,
                                   std::shared_ptr<Hero> hero,
                                   int range,
                                   const std::string& undead_type)
    : EntityAction(game, pos, std::static_pointer_cast<Entity>(hero)),
      undead_type_(undead_type),
      range_(range) {}

ActionResult NecromancyAction::perform() {
    if (Point::euclidean_ceil(entity()->position(), pos()) >= range_) {
        return ActionResult::fail();
    }
    if (auto corpse = std::dynamic_pointer_cast<Corpse>(
            game()->stage()->entity_at(pos()));
        corpse != nullptr) {
        auto& dead_mob_stats = corpse->dead_mob_stats();
        auto undead = game()->undead_registry().build(
            undead_type_,
            {corpse->dead_mob_race(), dead_mob_stats.attack,
             dead_mob_stats.moves, dead_mob_stats.damage, dead_mob_stats.vision,
             dead_mob_stats.hearing, dead_mob_stats.tracking, 0,
             dead_mob_stats.passability, entity()->faction().string(),
             dead_mob_stats.max_hp, dead_mob_stats.speed});
        undead->change_state(std::make_unique<WanderState>(undead));
        game()->stage()->replace_entity(game(), undead, pos());
        return ActionResult::succeed();
    }
    return ActionResult::fail();
}

}  // namespace rln
