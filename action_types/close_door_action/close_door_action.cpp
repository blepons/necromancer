#include "close_door_action.hpp"
#include <memory>
#include "action.hpp"
#include "entity_action.hpp"
#include "stage.hpp"
#include "tile.hpp"

namespace rln {

CloseDoorAction::CloseDoorAction(Game* game,
                                 Point pos,
                                 std::shared_ptr<Entity> entity,
                                 Point door_pos)
    : EntityAction(game, pos, entity), door_pos_(door_pos) {}

ActionResult CloseDoorAction::perform() {
    auto blocking_entity = game()->stage()->entity_at(door_pos_);
    if (blocking_entity != nullptr) {
        return ActionResult::fail();
    }
    game()->stage()->tile_at(door_pos_,
                             game()->tile_registry().build("closed_door"));
    // TODO: do something with this line after FOV was moved to Entity
    game()->stage()->fov_needs_update();
    return ActionResult::succeed();
}

}  // namespace rln
