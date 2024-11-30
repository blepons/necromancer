#include "spawn_action.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "stage.hpp"

namespace rln {

SpawnAction::SpawnAction(Game* game,
                         Point pos,
                         std::shared_ptr<Entity> entity,
                         const json& data)
    : EntityAction(game, pos, entity), data_(data) {}

ActionResult SpawnAction::perform() {
    std::string id = data_["id"];
    auto& plugin = game()->plugin(id);
    std::shared_ptr<Mob> spawned_mob = plugin.create_mob(data_);
    game()->stage()->add_entity(spawned_mob, pos());
    add_event(Event(Event::EventType::SPAWN, spawned_mob, pos()));
    return ActionResult::succeed();
}

}  // namespace rln
