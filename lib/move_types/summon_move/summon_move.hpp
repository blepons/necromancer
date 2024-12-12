#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include "move.hpp"

namespace rln {

class SummonMove : public Move {
public:
    SummonMove(int cooldown, const json& data);

    bool should_use(Game* game, std::shared_ptr<Mob> mob) const override;

    std::shared_ptr<Action> action(Game* game,
                                   std::shared_ptr<Mob> mob) override;

private:
    json data_;
};

}  // namespace rln
