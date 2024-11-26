#pragma once

#include <memory>
#include <queue>
#include <string>
#include "event.hpp"
#include "turn_result.hpp"

namespace rln {

class Hero;
class Action;
class Stage;
class PluginManager;
class MobPlugin;

// TODO
class Game {
public:
    std::shared_ptr<Hero> hero();

    Stage* stage();

    const MobPlugin& plugin(const std::string& id);

    TurnResult update();

    void add_action(Action* action);

    void add_event(Event event);

protected:
    TurnResult turn_result(bool game_changed);

private:
    std::shared_ptr<Hero> hero_;
    std::queue<Action*> actions_;
    std::vector<Action*> immediate_actions_;
    std::vector<Event> events_;
    Stage* stage_;
    PluginManager* plugin_manager_;
};

}  // namespace rln
