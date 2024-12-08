#pragma once

#include "entity.hpp"

namespace rln {

class Essence : public Entity {
public:
    Essence(int amount);

    std::string identifier() const override;

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

    int amount() const;

private:
    int amount_;
};

}  // namespace rln
