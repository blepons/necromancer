#pragma once

#include <memory>
#include <string>
#include <vector>
#include "attack.hpp"
#include "entity.hpp"

namespace rln {

class Move;

class Corpse : public Entity {
public:
    struct DeadMobStats {
        Attack attack;
        std::vector<std::shared_ptr<Move>> moves;
        int damage;
        int vision;
        int hearing;
        int tracking;
        Passability passability;
        int max_hp;
        int speed;
    };

    Corpse(int corpse_hp,
           std::string dead_mob_type,
           Attack attack,
           std::vector<std::shared_ptr<Move>> moves,
           int damage,
           int vision,
           int hearing,
           int tracking,
           Passability passability,
           int max_hp,
           int speed);

    std::shared_ptr<Action> action(Game* game) override;

    void attack(std::shared_ptr<Entity> target) override;

    bool on_take_damage(std::shared_ptr<Action> action,
                        int damage,
                        std::shared_ptr<Entity> source) override;

    void react_to_damage(std::shared_ptr<Action> action,
                         int damage,
                         std::shared_ptr<Entity> source) override;

    void on_death(std::shared_ptr<Action> action,
                  std::shared_ptr<Entity> source) override;

    void on_change_position(Game* game, Point from, Point to) override;

    void on_end_turn(std::shared_ptr<Action> action) override;

    std::string dead_mob_race() const;

    const DeadMobStats& dead_mob_stats() const;

private:
    std::string dead_mob_type_;
    DeadMobStats stats_;
};

}  // namespace rln
