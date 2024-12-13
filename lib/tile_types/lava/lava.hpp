#pragma once

#include <memory>
#include "tile.hpp"

namespace rln {

class Lava : public Tile {
public:
    Lava();

    std::shared_ptr<Action> on_turn(Game* game, Point position) const override;
};

}  // namespace rln
