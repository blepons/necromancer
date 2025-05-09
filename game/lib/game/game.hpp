#pragma once

#include <deque>
#include <limits>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>
#include "event.hpp"
#include "floor_manager.hpp"
#include "tile_registry.hpp"
#include "turn_result.hpp"
#include "undead_registry.hpp"

namespace rln {

class Hero;
class Fov;
class Action;
class Stage;
class MobPlugin;

// TODO
class Game {
public:
    Game(FloorManager* floor_manager,
         TileRegistry tile_registry,
         UndeadRegistry undead_registry);

    std::shared_ptr<Hero> hero();

    std::shared_ptr<const Hero> hero() const;

    void hero(std::shared_ptr<Hero> hero);

    const Fov& hero_fov() const;

    Stage* stage();

    const MobPlugin& plugin(const std::string& id);

    const TileRegistry& tile_registry() const;

    const UndeadRegistry& undead_registry() const;

    TurnResult update();

    void add_action(std::shared_ptr<Action> action);

    void add_event(Event event);

    int random(int min, int max = std::numeric_limits<int>::max());

    int unique_id();

    void assign_id(std::shared_ptr<Entity> entity);

    void reserve_id(int id);

    void next_floor();

protected:
    TurnResult turn_result(bool game_changed);

    FloorManager* floor_manager();

    void transfer_hero();

    void increment_entity_index();

private:
    FloorManager* floor_manager_;
    std::shared_ptr<Hero> hero_;

    bool tile_turn_processed_;
    bool stage_transfer_;

    std::deque<std::shared_ptr<Action>> actions_;
    std::mutex actions_mtx_;
    std::vector<Event> events_;

    TileRegistry tile_registry_;
    UndeadRegistry undead_registry_;

    std::mt19937 gen_;
    std::unordered_set<int> used_ids_;
};

}  // namespace rln
