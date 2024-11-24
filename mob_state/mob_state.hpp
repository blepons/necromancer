#pragma once

#include "point.hpp"

namespace rln {

class Action;
class Mob;
class Game;

class MobState {
public:
    MobState(Mob* mob);

    virtual ~MobState() = default;

    Mob* mob();

    Point position();

    virtual Action* action(Game* game) = 0;

protected:
    Mob* mob_;
};

}  // namespace rln
