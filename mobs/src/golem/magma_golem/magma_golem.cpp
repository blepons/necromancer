#include <memory>
#include <string>
#include <string_view>
#include "disappear_action.hpp"
#include "faction.hpp"
#include "hero.hpp"
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "plugin_keeper.hpp"
#include "set_block_action.hpp"

namespace rln {

class MagmaGolem : public Mob {
public:
    static constexpr std::string magma_golem_type = "magma_golem";
    static constexpr int damage_roll = 20;
    static constexpr int magma_golem_damage = 20;
    static constexpr int magma_golem_vision = 10;
    static constexpr int magma_golem_hearing = 5;
    static constexpr int magma_golem_tracking = 5;
    static constexpr int magma_golem_experience_reward = 50;
    static constexpr int magma_golem_max_hp = 150;
    static constexpr int magma_golem_speed = Energy::normal_speed;

    MagmaGolem(std::string_view faction)
        : Mob(magma_golem_type,
              Attack::melee(),
              {},
              magma_golem_damage,
              magma_golem_vision,
              magma_golem_hearing,
              magma_golem_tracking,
              magma_golem_experience_reward,
              Passability::door_or_walk(),
              std::move(faction),
              magma_golem_max_hp,
              magma_golem_speed) {}

    bool on_take_damage(std::shared_ptr<Action> action,
                        int damage,
                        std::shared_ptr<Entity>) override {
        if (action->game()->random(0, 100) >= damage_roll) {
            decrease_health(damage);
            return true;
        }
        return false;
    }

    void on_death(std::shared_ptr<Action> action,
                  std::shared_ptr<Entity> entity) override {
        if (auto hero = std::dynamic_pointer_cast<Hero>(entity);
            hero != nullptr) {
            hero->gain_experience(experience_reward());
        }
        action->add_action(std::make_shared<SetBlockAction>(
            action->game(), position(), shared_from_this(), "lava"));
        action->add_action(std::make_shared<DisappearAction>(
            action->game(), position(), shared_from_this()));
    }
};

class MagmaGolemPlugin : public MobPlugin {
public:
    std::string name() const override { return "magma_golem"; }

    std::string version() const override { return "0.0.1"; }

    std::string mob_identifier() const override {
        return MagmaGolem::magma_golem_type;
    }

    std::shared_ptr<Mob> create_mob(const json& data) const override {
        std::string faction = data.value("faction", std::string(Faction::none));
        return std::make_shared<MagmaGolem>(faction);
    }
};

}  // namespace rln

extern "C" const rln::MobPlugin& load_plugin() {
    static rln::MagmaGolemPlugin plugin;
    static auto keeper = PluginKeeper(plugin);
    return plugin;
}
