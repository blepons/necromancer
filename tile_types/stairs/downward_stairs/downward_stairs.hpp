#pragma once

#include "tile.hpp"
#include <memory>

namespace rln {

class DownwardStairs : public Tile {
public:
    DownwardStairs();

    std::shared_ptr<Action> on_turn(Game* game, Point position) const override;
};

}
