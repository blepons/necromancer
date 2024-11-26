#include "close_door_action.hpp"
#include <memory>
#include "action.hpp"
#include "entity_action.hpp"
#include "stage.hpp"
#include "tile.hpp"

// remove after implementing TileRegistry
#include <string_view>

namespace rln {

// TODO (make it a class)
class TileRegistry {
public:
    static TileType* get(std::string_view);
};

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
    game()->stage()->tile_at(door_pos_).type() =
        TileRegistry::get("closed_door");
    game()->stage()->fov_needs_update();
    return ActionResult::succeed();
}

}  // namespace rln
