#include "closed_door.hpp"
#include <memory>
#include "entity.hpp"
#include "open_door_action.hpp"

namespace rln {

ClosedDoor::ClosedDoor() : Tile("closed_door", Passability::door(), false) {}

bool ClosedDoor::can_operate() const {
    return true;
}

std::shared_ptr<Action> ClosedDoor::on_operate(Game* game,
                                               std::shared_ptr<Entity> entity,
                                               Point pos) const {
    return std::make_shared<OpenDoorAction>(game, entity->position(), entity,
                                            pos);
}

}  // namespace rln
