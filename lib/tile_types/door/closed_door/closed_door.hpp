#pragma once

#include <memory>
#include "tile.hpp"

namespace rln {

class ClosedDoor : public Tile {
    ClosedDoor();

    bool can_operate() const override;

    std::shared_ptr<Action> on_operate(Game* game,
                                       std::shared_ptr<Entity> entity,
                                       Point pos) const override;
};

}  // namespace rln
