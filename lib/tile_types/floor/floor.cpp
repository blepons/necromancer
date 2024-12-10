#include "floor.hpp"
#include <string>
#include <utility>

namespace rln {

Floor::Floor(std::string identifier)
    : Tile(std::move(identifier), Passability::walk(), true) {}

}  // namespace rln
