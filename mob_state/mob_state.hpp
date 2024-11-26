#pragma once

#include <memory>
#include "point.hpp"

namespace rln {

class Action;
class Mob;
class Game;

class MobState {
public:
    MobState(std::shared_ptr<Mob> mob);

    virtual ~MobState() = default;

    std::shared_ptr<Mob> mob();

    Point position();

    virtual std::unique_ptr<Action> action(Game* game) = 0;

protected:
    std::shared_ptr<Mob> mob_;
};

}  // namespace rln
