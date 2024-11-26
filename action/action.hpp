#pragma once

#include "event.hpp"
#include "game.hpp"
#include "point.hpp"
#include <memory>

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

    // TODO: const reference?
    void move_entity(std::shared_ptr<Entity> entity, Point destination);

protected:
    Game* game_;
    Point pos_;
};

struct ActionResult {
    ActionResult(bool success, bool done, std::unique_ptr<Action>&& alternative = nullptr);

    bool success;
    bool done;
    std::unique_ptr<Action> alternative;

    static ActionResult succeed() { return ActionResult(true, true); }

    static ActionResult fail() { return ActionResult(false, true); }

    static ActionResult alternate(std::unique_ptr<Action>&& alternative) {
        return ActionResult(false, true, std::move(alternative));
    }
};

}  // namespace rln
