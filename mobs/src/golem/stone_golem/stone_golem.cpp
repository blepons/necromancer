#include <memory>
#include <string>
#include "disappear_action.hpp"
#include "faction.hpp"
#include "hero.hpp"
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "plugin_keeper.hpp"
#include "set_block_action.hpp"

namespace rln {

class StoneGolem : public Mob {
public:
    static constexpr std::string stone_golem_type = "stone_golem";
    static constexpr int damage_roll = 40;
    static constexpr int stone_golem_damage = 40;
    static constexpr int stone_golem_vision = 10;
    static constexpr int stone_golem_hearing = 5;
    static constexpr int stone_golem_tracking = 5;
    static constexpr int stone_golem_experience_reward = 50;
    static constexpr int stone_golem_max_hp = 250;
    static constexpr int stone_golem_speed = Energy::normal_speed - 1;

    StoneGolem(std::string faction)
        : Mob(stone_golem_type,
              Attack::melee(),
              {},
              stone_golem_damage,
              stone_golem_vision,
              stone_golem_hearing,
              stone_golem_tracking,
              stone_golem_experience_reward,
              Passability::door_or_walk(),
              std::move(faction),
              stone_golem_max_hp,
              stone_golem_speed) {}

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
            action->game(), position(), shared_from_this(), "wall"));
        action->add_action(std::make_shared<DisappearAction>(
            action->game(), position(), shared_from_this()));
    }
};

class StoneGolemPlugin : public MobPlugin {
public:
    std::string name() const override { return "stone_golem"; }

    std::string version() const override { return "0.0.1"; }

    std::string mob_identifier() const override {
        return StoneGolem::stone_golem_type;
    }

    std::shared_ptr<Mob> create_mob(const json& data) const override {
        std::string faction = data.value("faction", Faction::none);
        return std::make_shared<StoneGolem>(faction);
    }
};

}  // namespace rln

extern "C" const rln::MobPlugin& load_plugin() {
    static rln::StoneGolemPlugin plugin;
    static auto keeper = PluginKeeper(plugin);
    return plugin;
}
