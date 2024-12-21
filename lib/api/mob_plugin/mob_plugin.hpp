#ifndef API_MOB_PLUGIN_HPP_
#define API_MOB_PLUGIN_HPP_

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

namespace rln {

using json = nlohmann::json;

class Mob;

/**
 * \brief Abstract base class for Mob plugins.
 *
 * The MobPlugin class defines the interface for creating and managing
 * different types of Mob entities in the game.
 * Derived classes must implement the specified methods to provide functionality
 * for specific Mob types.
 */
class MobPlugin {
public:
    /**
     * \brief Returns the name of the Mob plugin.
     *
     * \return A string representing the name of the plugin.
     */
    virtual std::string name() const = 0;

    /**
     * \brief Returns the version of the Mob plugin.
     *
     * \return A string representing the version of the plugin.
     */
    virtual std::string version() const = 0;

    virtual ~MobPlugin() = default;

    /**
     * \brief Returns the identifier for the Mob type created by this plugin.
     *
     * \return A string representing the Mob identifier.
     */
    virtual std::string mob_identifier() const = 0;

    /**
     * \brief Creates a Mob instance based on the provided JSON data.
     *
     * \param data A JSON object containing the data needed to create the Mob.
     * \return A shared pointer to the newly created Mob instance.
     */
    virtual std::shared_ptr<Mob> create_mob(const json& data) const = 0;
};

}  // namespace rln

#endif
