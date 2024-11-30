#ifndef API_MOB_PLUGIN_HPP_
#define API_MOB_PLUGIN_HPP_

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace rln {

class Mob;

class MobPlugin {
public:
    virtual std::string name() const = 0;

    virtual std::string version() const = 0;

    virtual ~MobPlugin() = default;

    virtual std::string mob_identifier() const = 0;

    virtual std::shared_ptr<Mob> create_mob(const json& data) const = 0;
};

}  // namespace rln

#endif
