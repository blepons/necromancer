#include <memory>
#include <string>
#include "faction.hpp"
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "plugin_keeper.hpp"

namespace rln {

class Orc : public Mob {
public:
    static constexpr std::string orc_type = "orc";
    static constexpr int orc_damage = 5;
    static constexpr int orc_vision = 15;
    static constexpr int orc_hearing = 15;
    static constexpr int orc_tracking = 15;
    static constexpr int orc_experience_reward = 40;
    static constexpr int orc_max_hp = 40;
    static constexpr int orc_speed = Energy::normal_speed;

    Orc(std::string faction)
        : Mob("orc",
              Attack::melee(),
              {},
              orc_damage,
              orc_vision,
              orc_hearing,
              orc_tracking,
              orc_experience_reward,
              Passability::door_or_walk(),
              std::move(faction),
              orc_max_hp,
              orc_speed) {}
};

class OrcPlugin : public MobPlugin {
public:
    std::string name() const override { return "orc"; }

    std::string version() const override { return "0.0.1"; }

    std::string mob_identifier() const override { return Orc::orc_type; }

    std::shared_ptr<Mob> create_mob(const json& data) const override {
        std::string faction = data.value("faction", Faction::none);
        return std::make_shared<Orc>(faction);
    }
};

}  // namespace rln

extern "C" const rln::MobPlugin& load_plugin() {
    static rln::OrcPlugin plugin;
    static auto keeper = PluginKeeper(plugin);
    return plugin;
}
