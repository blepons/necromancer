#pragma once

#include <memory>
#include <string>
#include "action.hpp"

namespace rln {

class Game;
class Mob;

class Move : public Serializable {
public:
    Move(int cooldown);

    virtual ~Move() = default;

    virtual std::string identifier() const = 0;

    json serialize() override;

    int cooldown() const;

    virtual bool should_use(Game* game, std::shared_ptr<Mob> mob) const;

    virtual bool should_use_on_damage(std::shared_ptr<Mob> mob,
                                      int damage) const;

    virtual std::shared_ptr<Action> action(Game* game,
                                           std::shared_ptr<Mob> mob) = 0;

private:
    int cooldown_;
};

}  // namespace rln
