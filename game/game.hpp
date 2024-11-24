#pragma once

#include <queue>
#include "event.hpp"
#include "turn_result.hpp"

namespace rln {

class Hero;
class Action;
class Stage;

// TODO
class Game {
public:
    Hero* hero();

    Stage* stage();

    TurnResult update();

    void add_action(Action* action);

    void add_event(Event event);

protected:
    TurnResult turn_result(bool game_changed);

private:
    Hero* hero_;
    std::queue<Action*> actions_;
    std::vector<Action*> immediate_actions_;
    std::vector<Event> events_;
    Stage* stage_;
};

}  // namespace rln
