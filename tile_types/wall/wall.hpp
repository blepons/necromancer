#pragma once

#include <string>
#include "tile.hpp"

namespace rln {

class Wall : public Tile {
    Wall(std::string identifier);
};

}  // namespace rln
