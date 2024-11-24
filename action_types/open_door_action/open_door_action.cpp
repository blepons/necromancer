#include "open_door_action.hpp"
#include "action.hpp"
#include "entity_action.hpp"
#include "stage.hpp"
#include "tile.hpp"
#include "tile_type.hpp"

#include <string_view>
// remove after implementing TileRegistry

namespace rln {

// TODO (make it a class)
class TileRegistry {
    static TileType* get(std::string_view);
};

OpenDoorAction::OpenDoorAction(Game* game,
                               Point pos,
                               Entity* entity,
                               Point door_pos)
    : EntityAction(game, pos, entity), door_pos_(door_pos) {}

ActionResult OpenDoorAction::perform() {
    game()->stage()->tile_at(door_pos_)->type() =
        TileRegistry::get("closed_door");
    game()->stage()->fov_needs_update();
    return ActionResult::succeed();
}

}  // namespace rln
