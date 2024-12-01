#pragma once

#include <cstddef>
#include <memory>
#include "entity.hpp"
#include "skill_set.hpp"

namespace rln {

class Hero : public Entity {
public:
    static constexpr std::size_t max_lvl = 100;

    int level() const;

    SkillSet& skill_set();

    int mana() const;

    int max_mana() const;

    void spend_mana(int amount);

    void gain_mana(int amount);

    std::shared_ptr<Action> action(Game* game) override;

    bool on_take_damage(std::shared_ptr<Action> action,
                        int damage,
                        std::shared_ptr<Entity> source) override;

    void on_death(std::shared_ptr<Action> action,
                  std::shared_ptr<Entity> source) override;

    void on_change_position(Game* game, Point from, Point to) override;

    void on_end_turn(std::shared_ptr<Action> action) override;

    void refresh_skills();

    // protected:
    //     constexpr int experience_needed_to_gain_lvl(int level);

private:
    int max_mana_;
    int mana_;
    int experience_;
    SkillSet skills_;
};

}  // namespace rln
