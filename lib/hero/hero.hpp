#pragma once

#include <array>
#include <cstddef>
#include <memory>
#include "direction.hpp"
#include "entity.hpp"
#include "skill_set.hpp"

namespace rln {

class Hero : public Entity {
public:
    Hero(int max_mana, SkillSet skills, int max_hp, int damage);

    void init(const json& data) override;

    std::string supertype() const override;

    std::string identifier() const override;

    json serialize() override;

    int level() const;

    void gain_experience(int amount);

    SkillSet& skill_set();

    int mana() const;

    int max_mana() const;

    void max_mana(int amount);

    void spend_mana(int amount);

    void gain_mana(int amount);

    int experience() const;

    void explore(Point pos, bool forced);

    void wait_for_input();

    void rest(Game* game);

    void walk(Game* game, Direction dir);

    bool needs_input() const override;

    std::shared_ptr<Action> action(Game* game) override;

    std::shared_ptr<Action> next_action();

    void next_action(std::shared_ptr<Action> action);

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

protected:
    static constexpr int max_lvl = 15;

    static constexpr std::array<int, max_lvl + 1> experience_needed_for_lvl = {
        0,   10,  25,   50,   100,  200,  300,  400,
        500, 750, 1000, 1250, 1500, 2000, 2500, 3000};

    void recalculate_level(int previous_lvl);

    void on_level_up(int previous_lvl, int new_lvl);

    static constexpr std::size_t hp_increment = 5;
    static constexpr std::size_t mp_increment = 10;

private:
    int max_mana_;
    int mana_;
    int experience_;
    SkillSet skills_;
    std::shared_ptr<Action> next_action_;
};

}  // namespace rln
