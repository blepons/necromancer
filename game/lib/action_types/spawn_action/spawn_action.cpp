#include "spawn_action.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "stage.hpp"
#include "wander_state.hpp"

namespace rln {

SpawnAction::SpawnAction(Game* game,
                         Point pos,
                         std::shared_ptr<Entity> entity,
                         const json& data)
    : EntityAction(game, pos, entity), data_(data) {}

ActionResult SpawnAction::perform() {
    std::string id = data_["identifier"];
    auto& plugin = game()->plugin(id);
    std::shared_ptr<Mob> spawned_mob = plugin.create_mob(data_);
    spawned_mob->faction().set(entity()->faction().string());
    game()->stage()->add_entity(game(), spawned_mob, pos());
    spawned_mob->change_state(std::make_unique<WanderState>(spawned_mob));
    add_event(Event(Event::EventType::SPAWN, spawned_mob, pos()));
    return ActionResult::succeed();
}

}  // namespace rln
