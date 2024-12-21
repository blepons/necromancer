#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <ostream>
#include <string>
#include "floor.hpp"
#include "game.hpp"
#include "input_handler.hpp"
#include "json_floor_manager.hpp"
#include "lava.hpp"
#include "library_manager.hpp"
#include "renderer.hpp"
#include "stairs.hpp"
#include "tile_registry.hpp"
#include "undead_registry.hpp"
#include "wall.hpp"

using json = nlohmann::json;

LibraryManager make_library_manager(std::vector<std::string> paths);

std::unique_ptr<rln::JsonFloorManager> make_floor_manager(
    std::vector<std::string> stages);

rln::TileRegistry make_tile_registry();

rln::UndeadRegistry make_undead_registry();

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Config file missing" << std::endl;
        return 0;
    }
    std::ifstream ifs(argv[1]);
    json config = json::parse(ifs);

    auto lib_manager = make_library_manager(config["libraries"]);
    auto floor_manager = make_floor_manager(config["stages"]);
    auto game = std::make_unique<rln::Game>(
        floor_manager.get(), make_tile_registry(), make_undead_registry());

    rln::Renderer renderer(game.get(), config["textures"]);
    auto& window = renderer.window();
    rln::InputHandler input_handler(game.get(), renderer);

    game->next_floor();

    while (window.isOpen()) {
        game->update();
        renderer.render();
        input_handler.handle_input();
    }
}

LibraryManager make_library_manager(std::vector<std::string> paths) {
    static constexpr std::string extension = ".so";
    static constexpr std::string symbol = "load_plugin";

    LibraryManager libraries;
    for (const auto& path : paths) {
        libraries.scan(path, extension, symbol);
    }
    return libraries;
}

std::unique_ptr<rln::JsonFloorManager> make_floor_manager(
    std::vector<std::string> stages) {
    return std::make_unique<rln::JsonFloorManager>(stages);
}

rln::TileRegistry make_tile_registry() {
    rln::TileRegistry tiles;
    tiles.add("wall", []() { return std::make_shared<rln::Wall>("wall"); });
    tiles.add("floor", []() { return std::make_shared<rln::Floor>("floor"); });
    tiles.add("lava", []() { return std::make_shared<rln::Lava>(); });
    tiles.add("upward_stairs",
              []() { return std::make_shared<rln::UpwardStairs>(); });
    tiles.add("downward_stairs",
              []() { return std::make_shared<rln::DownwardStairs>(); });
    return tiles;
}

rln::UndeadRegistry make_undead_registry() {
    rln::UndeadRegistry undeads;
    undeads.add("ghost", [](rln::UndeadRegistry::UndeadParams&& params) {
        return std::make_shared<rln::Undead>(
            "ghost", 0.5, params.race, params.attack, params.moves,
            params.damage, params.vision, params.hearing, params.tracking,
            params.experience_reward, params.passability, params.faction,
            params.max_hp, params.speed);
    });
    undeads.add("skeleton", [](rln::UndeadRegistry::UndeadParams&& params) {
        return std::make_shared<rln::Undead>(
            "skeleton", 0.7, params.race, params.attack, params.moves,
            params.damage, params.vision, params.hearing, params.tracking,
            params.experience_reward, params.passability, params.faction,
            params.max_hp, params.speed);
    });
    undeads.add("mummy", [](rln::UndeadRegistry::UndeadParams&& params) {
        return std::make_shared<rln::Undead>(
            "mummy", 0.8, params.race, params.attack, params.moves,
            params.damage, params.vision, params.hearing, params.tracking,
            params.experience_reward, params.passability, params.faction,
            params.max_hp, params.speed);
    });
    undeads.add("zombie", [](rln::UndeadRegistry::UndeadParams&& params) {
        return std::make_shared<rln::Undead>(
            "zombie", 0.9, params.race, params.attack, params.moves,
            params.damage, params.vision, params.hearing, params.tracking,
            params.experience_reward, params.passability, params.faction,
            params.max_hp, params.speed);
    });
    undeads.add("ghoul", [](rln::UndeadRegistry::UndeadParams&& params) {
        return std::make_shared<rln::Undead>(
            "ghoul", 1.5, params.race, params.attack, params.moves,
            params.damage, params.vision, params.hearing, params.tracking,
            params.experience_reward, params.passability, params.faction,
            params.max_hp, params.speed);
    });
    return undeads;
}
