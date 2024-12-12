#include "tile_builder.hpp"
#include <memory>
#include <string>
#include "game.hpp"

namespace rln {

std::shared_ptr<Tile> TileBuilder::build(Game* game, std::string identifier) {
    return game->tile_registry().build(identifier);
}

}  // namespace rln
