#pragma once

#include <string>
#include "tile.hpp"

namespace rln {

class Floor : public Tile {
public:
    Floor(std::string identifier);
};

}  // namespace rln
