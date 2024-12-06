#include "open_door_action.hpp"
#include <memory>
#include "action.hpp"
#include "entity_action.hpp"
#include "stage.hpp"
#include "tile.hpp"

namespace rln {

OpenDoorAction::OpenDoorAction(Game* game,
                               Point pos,
                               std::shared_ptr<Entity> entity,
                               Point door_pos)
    : EntityAction(game, pos, entity), door_pos_(door_pos) {}

ActionResult OpenDoorAction::perform() {
    game()->stage()->tile_at(door_pos_,
                             game()->tile_registry().build("open_door"));
    // TODO: do something with this line after FOV was moved to Entity
    game()->stage()->fov_needs_update();
    return ActionResult::succeed();
}

}  // namespace rln
