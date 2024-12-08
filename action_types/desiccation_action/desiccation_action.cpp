#include "desiccation_action.hpp"
#include <memory>
#include "corpse.hpp"
#include "hero.hpp"
#include "mana_gain_action.hpp"
#include "stage.hpp"

// TODO: add support for healing
// #include "heal_action.hpp"

namespace rln {

DesiccationAction::DesiccationAction(Game* game,
                                     Point pos,
                                     std::shared_ptr<Hero> hero,
                                     int range,
                                     int stat_increment)
    : EntityAction(game, pos, std::static_pointer_cast<Entity>(hero)),
      range_(range),
      stat_increment_(stat_increment) {}

ActionResult DesiccationAction::perform() {
    if (Point::euclidean_ceil(entity()->position(), pos()) >= range_) {
        return ActionResult::fail();
    }
    if (auto corpse = game()->stage()->entity_at(pos());
        std::dynamic_pointer_cast<Corpse>(corpse) != nullptr) {
        corpse->take_damage(shared_from_this(), 100000, entity());
        return ActionResult::alternate(std::make_shared<ManaGainAction>(
            game(), entity()->position(),
            std::static_pointer_cast<Hero>(entity()), stat_increment_));
    }
    return ActionResult::fail();
}

}  // namespace rln
