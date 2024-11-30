#pragma once

#include <memory>
#include "energy.hpp"
#include "passability.hpp"
#include "point.hpp"
#include "fov.hpp"

namespace rln {

class Action;
class Game;

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity(Passability passability, int max_hp, int speed, Point position);

    virtual ~Entity() = default;

    Energy& energy();

    Passability passability() const;

    Fov& fov();

    int max_health() const;

    int health() const;

    void increase_health(int amount);

    void decrease_health(int amount);

    void health(int amount);

    bool alive() const;

    int speed() const;

    Point position() const;

    void position(Point point);

    void move(Point point, Game* game);

    bool take_damage(std::shared_ptr<Action> action,
                     int damage,
                     std::shared_ptr<Entity> source);

    void end_turn(std::shared_ptr<Action> action);

    virtual bool needs_input() const;

    virtual std::shared_ptr<Action> action(Game* game) = 0;

    virtual bool attack(std::shared_ptr<Entity> target) = 0;

    virtual void on_take_damage(std::shared_ptr<Action> action,
                                int damage,
                                std::shared_ptr<Entity> source) = 0;

    virtual void on_death(std::shared_ptr<Action> action,
                          std::shared_ptr<Entity> source) = 0;

    virtual void on_change_position(Game* game, Point from, Point to) = 0;

    virtual void on_end_turn(std::shared_ptr<Action> action) = 0;

protected:
    Energy energy_;
    Passability passability_;
    Fov fov_;

    int max_hp_;
    int hp_;
    int speed_;

    Point position_;
};

}  // namespace rln
