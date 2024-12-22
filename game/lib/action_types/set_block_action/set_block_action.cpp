#include "set_block_action.hpp"
#include "stage.hpp"

namespace rln {

SetBlockAction::SetBlockAction(Game* game,
                               Point pos,
                               std::shared_ptr<Entity> entity,
                               std::string tile_id)
    : EntityAction(game, pos, entity), tile_id_(std::move(tile_id)) {}

ActionResult SetBlockAction::perform() {
    game()->stage()->tile_at(pos(), game()->tile_registry().build(tile_id_));
    return ActionResult::succeed();
}

}  // namespace rln
