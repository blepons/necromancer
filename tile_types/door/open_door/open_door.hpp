#pragma once

#include <memory>
#include "tile.hpp"

namespace rln {

class OpenDoor : public Tile {
    OpenDoor();

    bool can_operate() const override;

    std::shared_ptr<Action> on_operate(Game* game,
                                       std::shared_ptr<Entity> entity,
                                       Point pos) const override;
};

}  // namespace rln
