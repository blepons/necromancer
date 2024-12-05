#include "open_door.hpp"
#include <memory>
#include "close_door_action.hpp"
#include "entity.hpp"

namespace rln {

OpenDoor::OpenDoor() : Tile("open_door", Passability::walk(), true) {}

bool OpenDoor::can_operate() const {
    return true;
}

std::shared_ptr<Action> OpenDoor::on_operate(Game* game,
                                             std::shared_ptr<Entity> entity,
                                             Point pos) const {
    return std::make_shared<CloseDoorAction>(game, entity->position(), entity,
                                             pos);
}

}  // namespace rln
