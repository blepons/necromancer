#pragma once

#include "event.hpp"
#include "game.hpp"
#include "point.hpp"

namespace rln {

struct ActionResult;
class Entity;

class Action {
public:
    Action(Game* game, Point pos);

    virtual ~Action() = default;

    Game* game() const;

    Point pos() const;

    virtual ActionResult perform() = 0;

    virtual bool immediate() const;

    void add_action(Action* action);

    void add_event(Event event);

    void move_entity(Entity* entity, Point destination);

protected:
    Game* game_;
    Point pos_;
};

struct ActionResult {
    ActionResult(bool success, bool done, Action* alternative = nullptr);

    bool success;
    bool done;
    Action* alternative = nullptr;

    static ActionResult succeed() { return ActionResult(true, true, nullptr); }

    static ActionResult fail() { return ActionResult(false, true, nullptr); }

    static ActionResult alternate(Action* alternative) {
        return ActionResult(false, true, alternative);
    }
};

}  // namespace rln
