#include "tile_registry.hpp"
#include <memory>
#include <string>
#include <utility>
#include "tile.hpp"

namespace rln {

void TileRegistry::add(const std::string& identifier, TileFactory&& factory) {
    tile_factories_[identifier] = std::move(factory);
}

std::unique_ptr<Tile> TileRegistry::build(const std::string& identifier) const {
    return tile_factories_.at(identifier)();
}

}  // namespace rln
