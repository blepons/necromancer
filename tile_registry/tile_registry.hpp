#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace rln {

class Tile;

class TileRegistry {
public:
    using TileFactory = std::function<std::shared_ptr<Tile>()>;

    TileRegistry() = default;

    void add(const std::string& identifier, TileFactory&& factory);

    std::shared_ptr<Tile> build(const std::string& identifier) const;

private:
    std::unordered_map<std::string, TileFactory> tile_factories_;
};

}  // namespace rln
