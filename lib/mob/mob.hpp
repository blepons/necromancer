#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "attack.hpp"
#include "entity.hpp"
#include "mob_state.hpp"

namespace rln {

class Move;

class Mob : public Entity {
public:
    Mob(std::string race,
        Attack attack,
        std::vector<std::shared_ptr<Move>> moves,
        int damage,
        int vision,
        int hearing,
        int tracking,
        int experience_reward,
        Passability passability,
        std::string faction,
        int max_hp,
        int speed);

    std::shared_ptr<Mob> getptr();

    void init(const json& data) override;

    std::string identifier() const override;

    json serialize() override;

    void use_move(std::shared_ptr<Move> move);

    bool can_use_move(std::shared_ptr<Move> move);

    bool needs_input() const override final;

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

    std::string race() const;

    int vision() const;

    int hearing() const;

    int tracking() const;

    int experience_reward() const;

    MobState& state();

    void change_state(std::unique_ptr<MobState>&& new_state);

    bool asleep() const;

    bool wandering() const;

    bool entity_nearby(Game* game, int distance);

protected:
    std::string race_;
    Attack attack_;
    std::unordered_map<std::shared_ptr<Move>, int> cooldowns_;

    int vision_;
    int hearing_;
    int tracking_;
    int experience_reward_;

    std::unique_ptr<MobState> state_;
};

}  // namespace rln
