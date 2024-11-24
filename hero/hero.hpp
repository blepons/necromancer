#pragma once

#include <cstddef>
#include "entity.hpp"
#include "skill_set.hpp"

namespace rln {

class Hero : public Entity {
public:
    static constexpr std::size_t max_lvl = 100;

    int level() const;

    SkillSet* skills();

    int max_health() const override;

    int speed() const override;

    int mana() const;

    int max_mana() const;

    void spend_mana(int amount);

    void gain_mana(int amount);

    Action* action(Game* game) override;

    void on_take_damage(Action* action, int damage, Entity* source) override;

    void on_death(Action* action, Entity* source) override;

    void on_change_position(Game* game, Point from, Point to) override;

    void on_end_turn(Action* action) override;

    // void see_entity(Entity* entity);  // see_mob

    void refresh_skills();

    // protected:
    //     constexpr int experience_needed_to_gain_lvl(int level);

private:
    int max_health_;
    int mana_;
    int max_mana_;
    int experience_;
    SkillSet* skills_;
};

}  // namespace rln
