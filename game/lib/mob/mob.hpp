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
/**
 * \brief Represents a mob in the game.
 */
class Mob : public Entity {
public:
    /**
     * \brief Constructs a Mob instance.
     *
     * \param race The race of the mob.
     * \param attack The attack type of the mob.
     * \param moves A vector of moves available to the mob.
     * \param damage The base damage the mob can inflict.
     * \param vision The visibility range of the mob.
     * \param hearing The hearing range of the mob.
     * \param tracking The tracking range of the mob.
     * \param experience_reward The experience points awarded for defeating
     *                          the mob.
     * \param passability The passability type of the mob.
     * \param faction The faction to which the mob belongs.
     * \param max_hp The maximum hit points of the mob.
     * \param speed The speed of the mob.
     *              (The index of Energy::speed_gains)
     */
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

    /**
     * \brief Returns a shared pointer to the current Mob instance.
     *
     * \return A shared pointer to this Mob.
     */
    std::shared_ptr<Mob> getptr();

    /**
     * \brief Initializes the Mob instance with data from a JSON object.
     *
     * \param data The JSON object containing initialization data.
     */
    void init(const json& data) override;

    /**
     * \brief Returns the supertype of the Mob.
     *
     * \return A string representing the supertype.
     */
    std::string supertype() const override;

    /**
     * \brief Returns a race of the Mob.
     *
     * \return A string representing Mob's race.
     */
    std::string identifier() const override;

    /**
     * \brief Serializes the Mob instance to a JSON object.
     *
     * \return A JSON object representing the Mob.
     */
    json serialize() override;

    /**
     * \brief Uses a specified move.
     *
     * \param move A shared pointer to the move to be used.
     */
    void use_move(std::shared_ptr<Move> move);

    /**
     * \brief Checks if the Mob can use a specified move.
     *
     * \param move A shared pointer to the move to check.
     * \return True if the move can be used, false otherwise.
     */
    bool can_use_move(std::shared_ptr<Move> move);

    /**
     * \brief Checks if the Mob requires input for its next action.
     *
     * \return False.
     */
    bool needs_input() const override final;

    /**
     * \brief Returns the action the Mob will take during its turn.
     *
     * \param game A pointer to the current game instance.
     * \return A shared pointer to the action to be performed.
     */
    std::shared_ptr<Action> action(Game* game) override;

    /**
     * \brief Executes an attack on a target entity.
     *
     * \param action A shared pointer to the action being performed.
     * \param target A shared pointer to the target entity.
     */
    void attack(std::shared_ptr<Action> action,
                std::shared_ptr<Entity> target) override;

    /**
     * \brief Handles the event of taking damage.
     *
     * \param action A shared pointer to the action causing the damage.
     * \param damage The amount of damage taken.
     * \param source A shared pointer to the entity causing the damage.
     * \return True if the Mob has taken damage, false otherwise.
     */
    bool on_take_damage(std::shared_ptr<Action> action,
                        int damage,
                        std::shared_ptr<Entity> source) override;

    /**
     * \brief Reacts to damage taken from a source.
     *
     * \param action A shared pointer to the action causing the damage.
     * \param damage The amount of damage taken.
     * \param source A shared pointer to the entity causing the damage.
     */
    void react_to_damage(std::shared_ptr<Action> action,
                         int damage,
                         std::shared_ptr<Entity> source) override;

    /**
     * \brief Handles the event of the Mob's death.
     *
     * This method is called when the Mob's hit points reach zero.
     *
     * \param action A shared pointer to the action that caused the death.
     * \param source A shared pointer to the entity that dealt the final blow.
     */
    void on_death(std::shared_ptr<Action> action,
                  std::shared_ptr<Entity> source) override;

    /**
     * \brief Handles the event of the Mob changing position on the game map.
     *
     * \param game A pointer to the current game instance.
     * \param from The previous position of the Mob.
     * \param to The new position of the Mob.
     */
    void on_change_position(Game* game, Point from, Point to) override;

    /**
     * \brief Handles the end of the Mob's turn.
     *
     * \param action A shared pointer to the action that was performed during
     * the turn.
     */
    void on_end_turn(std::shared_ptr<Action> action) override;

    /**
     * \brief Returns the race of the Mob.
     *
     * \return A string representing the race of the Mob.
     */
    std::string race() const;

    /**
     * \brief Returns a reference to the Mob's attack type.
     *
     * \return A reference to the Attack object associated with the Mob.
     */
    Attack& attack();

    /**
     * \brief Returns the vision range of the Mob.
     *
     * \return An integer representing the vision range.
     */
    int vision() const;

    /**
     * \brief Returns the hearing range of the Mob.
     *
     * \return An integer representing the hearing range.
     */
    int hearing() const;

    /**
     * \brief Returns the tracking ability of the Mob.
     *
     * \return An integer representing the tracking ability.
     */
    int tracking() const;

    /**
     * \brief Returns the experience reward for defeating the Mob.
     *
     * \return An integer representing the experience reward.
     */
    int experience_reward() const;

    /**
     * \brief Returns a reference to the Mob's current state.
     *
     * \return A reference to the MobState object representing the current
     * state.
     */
    MobState& state();

    /**
     * \brief Returns a map of moves and their cooldowns.
     *
     * \return A reference to an unordered map where keys are shared pointers to
     * Move objects and values are integers representing the cooldowns.
     */
    std::unordered_map<std::shared_ptr<Move>, int>& moves();

    /**
     * \brief Changes the current state of the Mob to a new state.
     *
     * \param new_state A unique pointer to the new MobState to transition to.
     */
    void change_state(std::unique_ptr<MobState>&& new_state);

    /**
     * \brief Checks if the Mob is asleep.
     *
     * \return True if the Mob is asleep, false otherwise.
     */
    bool asleep() const;

    /**
     * \brief Checks if the Mob is wandering.
     *
     * \return True if the Mob is wandering, false otherwise.
     */
    bool wandering() const;

    /**
     * \brief Checks if there is an entity nearby within a specified distance.
     *
     * \param game A pointer to the current game instance.
     * \param distance The distance within which to check for nearby entities.
     * \return True if an entity is nearby, false otherwise.
     */
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
