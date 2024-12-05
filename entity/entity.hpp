#pragma once

#include <memory>
#include "energy.hpp"
#include "faction.hpp"
#include "fov.hpp"
#include "passability.hpp"
#include "point.hpp"

namespace rln {

class Action;
class Game;

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity(Passability passability, std::string faction, int max_hp, int speed);

    virtual ~Entity() = default;

    virtual void init(Point pos);

    int id() const;

    void id(int id);

    Energy& energy();

    Passability passability() const;

    Fov& fov();

    Faction& faction();

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

    virtual void attack(std::shared_ptr<Entity> target) = 0;

    virtual bool on_take_damage(std::shared_ptr<Action> action,
                                int damage,
                                std::shared_ptr<Entity> source) = 0;

    virtual void react_to_damage(std::shared_ptr<Action> action,
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
    Faction faction_;

    int max_hp_;
    int hp_;
    int speed_;

    Point position_;
    int id_;
};

}  // namespace rln
