#pragma once

#include <deque>
#include <memory>
#include <string>
#include "event.hpp"
#include "turn_result.hpp"

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

    TurnResult update();

    void add_action(std::shared_ptr<Action> action);

    void add_event(Event event);

    int random(int min, int max);

    int unique_id();

    void assign_id(std::shared_ptr<Entity> entity);

    void next_floor();

protected:
    TurnResult turn_result(bool game_changed);

private:
    Stage* stage_;
    std::shared_ptr<Hero> hero_;

    std::deque<std::shared_ptr<Action>> actions_;
    std::vector<Event> events_;
};

}  // namespace rln
