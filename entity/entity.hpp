#pragma once

#include "energy.hpp"
#include "passability.hpp"
#include "point.hpp"

namespace rln {

class Action;
class Game;

class Entity {
public:
    Entity(Passability passability, int max_hp, int speed, Point position);

    virtual ~Entity() = default;

    Passability passability() const;

    int max_health() const;

    int health() const;

    void increase_health(int amount);

    void decrease_health(int amount);

    void health(int amount);

    bool alive() const;

    int speed() const;

    Point position() const;

    void position(Point point, Game* game);

    bool take_damage(Action* action, int damage, Entity* source);

    void end_turn(Action* action);

    virtual bool needs_input() const;

    virtual Action* action(Game* game) = 0;

    virtual bool attack(Entity* target) = 0;

    virtual void on_take_damage(Action* action, int damage, Entity* source) = 0;

    virtual void on_death(Action* action, Entity* source) = 0;

    virtual void on_change_position(Game* game, Point from, Point to) = 0;

    virtual void on_end_turn(Action* action) = 0;

protected:
    Energy energy_;
    Passability passability_;

    int max_hp_;
    int hp_;
    int speed_;

    Point position_;
};

}  // namespace rln
