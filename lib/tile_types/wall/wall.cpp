#include "wall.hpp"
#include <string>
#include <utility>

namespace rln {

Wall::Wall(std::string identifier)
    : Tile(std::move(identifier), Passability::none(), false) {}

}  // namespace rln
