#pragma once

#include <memory>
#include <string>
#include "tile.hpp"

namespace rln {

class TileBuilder {
public:
    static std::shared_ptr<Tile> build(Game* game, std::string identifier);
};

}  // namespace rln
