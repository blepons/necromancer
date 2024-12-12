#pragma once

#include <memory>
#include <string>
#include "point.hpp"
#include "serializable.hpp"

namespace rln {

class Action;
class Mob;
class Game;

class MobState : public Serializable {
public:
    MobState(std::shared_ptr<Mob> mob);

    virtual ~MobState() = default;

    virtual std::string identifier() const = 0;

    json serialize() override;

    std::shared_ptr<Mob> mob();

    Point position();

    virtual std::shared_ptr<Action> action(Game* game) = 0;

protected:
    std::shared_ptr<Mob> mob_;
};

}  // namespace rln
