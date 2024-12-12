#include "json_floor_manager.hpp"
#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "entity_builder.hpp"
#include "game.hpp"
#include "hero.hpp"
#include "stage.hpp"
#include "tile_builder.hpp"

namespace rln {

using json = nlohmann::json;
namespace fs = std::filesystem;

JsonFloorManager::JsonFloorManager(const std::vector<std::string>& stage_paths)
    : stage_paths_(stage_paths),
      current_stage_index_(index_not_loaded_yet),
      stage_(nullptr) {}

Stage* JsonFloorManager::stage() {
    return stage_.get();
}

int JsonFloorManager::index() const {
    return current_stage_index_;
}

void JsonFloorManager::index(int new_index) {
    current_stage_index_ = new_index;
}

void JsonFloorManager::next_index() {
    if (index() == index_not_loaded_yet) {
        index(0);
    } else {
        index(index() + 1);
    }
    if (index() == stage_paths_.size()) {
        index(index_finished);
    }
}

void JsonFloorManager::load_next_floor(Game* game) {
    next_index();
    if (index() == index_finished) {
        // TODO: finish the game
    }
    fs::path stage_path(stage_paths_[index()]);
    std::ifstream ifs(stage_path);
    json jf = json::parse(ifs);

    auto rows = jf["stage"]["rows"].template get<int>();
    auto columns = jf["stage"]["columns"].template get<int>();
    auto map = jf["stage"]["map"];
    auto start_pos = jf["stage"]["start_pos"];

    bpns::matrix<std::shared_ptr<Tile>> tiles(rows, columns);
    for (auto r = 0; r < rows; ++r) {
        for (auto c = 0; c < columns; ++c) {
            tiles(r, c) =
                TileBuilder::build(game, map[r][c].template get<std::string>());
        }
    }

    auto entities = jf["entities"];

    std::vector<std::shared_ptr<Entity>> parsed_entities;
    for (const auto& entity_data : entities) {
        parsed_entities.emplace_back(EntityBuilder::build(game, entity_data));
        if (entity_data["identifier"] == "hero") {
            game->hero(std::static_pointer_cast<Hero>(parsed_entities.back()));
        }
    }

    // TODO: should Stage ctor perfect forward args?
    stage_ = std::make_unique<Stage>(parsed_entities, tiles,
                                     Point(start_pos[0], start_pos[1]));
}

void JsonFloorManager::unload_current_floor() {}

}  // namespace rln
