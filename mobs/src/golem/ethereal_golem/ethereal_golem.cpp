#include <memory>
#include <string>
#include <string_view>
#include "disappear_action.hpp"
#include "faction.hpp"
#include "hero.hpp"
#include "mob.hpp"
#include "mob_plugin.hpp"
#include "plugin_keeper.hpp"
#include "essence.hpp"
#include "stage.hpp"

namespace rln {

class SpawnEssenceAction : public Action {
public:
    SpawnEssenceAction(Game* game, Point pos, int amount)
        : Action(game, pos), amount_(amount) {}

    ActionResult perform() override {
        auto essence = std::make_shared<Essence>(amount_);
        game()->stage()->add_entity(game(), essence, pos());
        return ActionResult::succeed();
    }

private:
    int amount_;
};

class EtherealGolem : public Mob {
public:
    static constexpr std::string ethereal_golem_type = "ethereal_golem";
    static constexpr int damage_roll = 50;
    static constexpr int ethereal_golem_damage = 15;
    static constexpr int ethereal_golem_vision = 10;
    static constexpr int ethereal_golem_hearing = 5;
    static constexpr int ethereal_golem_tracking = 5;
    static constexpr int ethereal_golem_experience_reward = 50;
    static constexpr int ethereal_golem_max_hp = 100;
    static constexpr int ethereal_golem_speed = Energy::normal_speed;

    EtherealGolem(std::string_view faction)
        : Mob(ethereal_golem_type,
              Attack::melee(),
              {},
              ethereal_golem_damage,
              ethereal_golem_vision,
              ethereal_golem_hearing,
              ethereal_golem_tracking,
              ethereal_golem_experience_reward,
              Passability::door_or_walk(),
              std::move(faction),
              ethereal_golem_max_hp,
              ethereal_golem_speed) {}

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
        action->add_action(std::make_shared<DisappearAction>(
            action->game(), position(), shared_from_this()));
        action->add_action(std::make_shared<SpawnEssenceAction>(
            action->game(), position(), 50
        ));
    }
};

class EtherealGolemPlugin : public MobPlugin {
public:
    std::string name() const override { return "ethereal_golem"; }

    std::string version() const override { return "0.0.1"; }

    std::string mob_identifier() const override {
        return EtherealGolem::ethereal_golem_type;
    }

    std::shared_ptr<Mob> create_mob(const json& data) const override {
        std::string faction = data.value("faction", std::string(Faction::none));
        return std::make_shared<EtherealGolem>(faction);
    }
};

}  // namespace rln

extern "C" const rln::MobPlugin& load_plugin() {
    static rln::EtherealGolemPlugin plugin;
    static auto keeper = PluginKeeper(plugin);
    return plugin;
}
