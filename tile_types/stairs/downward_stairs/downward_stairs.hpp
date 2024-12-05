#pragma once

#include <memory>
#include "tile.hpp"

namespace rln {

class DownwardStairs : public Tile {
public:
    DownwardStairs();

    std::shared_ptr<Action> on_turn(Game* game, Point position) const override;
};

}  // namespace rln
