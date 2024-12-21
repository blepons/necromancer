#include "entity_action.hpp"
#include <memory>

namespace rln {

EntityAction::EntityAction(Game* game,
                           Point pos,
                           std::shared_ptr<Entity> entity)
    : Action(game, pos), entity_(entity) {}

std::shared_ptr<Entity> EntityAction::entity() {
    return entity_;
}

}  // namespace rln
