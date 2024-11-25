#include "entity_action.hpp"

namespace rln {

EntityAction::EntityAction(Game* game, Point pos, Entity* entity)
    : Action(game, pos), entity_(entity) {}

Entity* EntityAction::entity() {
    return entity_;
}

}  // namespace rln
