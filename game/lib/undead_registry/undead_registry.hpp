#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "undead.hpp"

namespace rln {

class UndeadRegistry {
public:
    struct UndeadParams {
        std::string race;
        Attack attack;
        std::vector<std::shared_ptr<Move>> moves;
        int damage;
        int vision;
        int hearing;
        int tracking;
        int experience_reward;
        Passability passability;
        std::string faction;
        int max_hp;
        int speed;
    };
    using UndeadFactory =
        std::function<std::shared_ptr<Undead>(float, UndeadParams&&)>;

    UndeadRegistry() = default;

    void add(const std::string& identifier,
             float multiplier,
             UndeadFactory&& factory);

    std::shared_ptr<Undead> build(const std::string& identifier,
                                  UndeadParams&& params) const;

    float multiplier(const std::string& identifier) const;

private:
    std::unordered_map<std::string, UndeadFactory> undead_factories_;
    std::unordered_map<std::string, float> undead_multipliers_;
};

}  // namespace rln
