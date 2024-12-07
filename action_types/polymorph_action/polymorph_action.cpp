#include "polymorph_action.hpp"
#include <algorithm>
#include <memory>
#include "entity.hpp"
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "stage.hpp"

namespace rln {

PolymorphAction::PolymorphAction(Game* game,
                                 Point pos,
                                 std::shared_ptr<Entity> entity,
                                 const json& data)
    : EntityAction(game, pos, entity), data_(data) {}

ActionResult PolymorphAction::perform() {
    float hp_fraction =
        static_cast<float>(entity()->health()) / entity()->max_health();
    std::string id = data_["id"];
    auto& plugin = game()->plugin(id);
    std::shared_ptr<Mob> spawned_mob = plugin.create_mob(data_);
    spawned_mob->health(
        std::max(static_cast<int>(hp_fraction * spawned_mob->max_health()), 1));
    spawned_mob->energy() = entity()->energy();
    game()->stage()->replace_entity(game(), spawned_mob, entity()->position());
    add_event(Event(Event::EventType::POLYMORPH, spawned_mob,
                    spawned_mob->position()));
    return ActionResult::succeed();
}

}  // namespace rln
