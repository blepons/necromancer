#pragma once

#include <deque>
#include <limits>
#include <memory>
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
class Action;
class Stage;
class MobPlugin;

// TODO
class Game {
public:
    // TODO: ctor

    std::shared_ptr<Hero> hero();

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

    void next_floor();

protected:
    TurnResult turn_result(bool game_changed);

    FloorManager* floor_manager();

    void transfer_hero();

private:
    FloorManager* floor_manager_;
    std::shared_ptr<Hero> hero_;

    std::deque<std::shared_ptr<Action>> actions_;
    std::vector<Event> events_;

    TileRegistry tile_registry_;
    UndeadRegistry undead_registry_;

    std::mt19937 gen_;
    std::unordered_set<int> used_ids_;
};

}  // namespace rln
