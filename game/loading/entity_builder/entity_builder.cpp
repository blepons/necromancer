#include "entity_builder.hpp"
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "curse_skill.hpp"
#include "desiccation_skill.hpp"
#include "game.hpp"
#include "hero.hpp"
#include "mob_plugin.hpp"
#include "necromancy_skill.hpp"
#include "polymorph_skill.hpp"
#include "skill_set.hpp"
#include "wrath_skill.hpp"

namespace rln {

std::shared_ptr<Entity> EntityBuilder::build(Game* game,
                                             const json& entity_data) {
    auto supertype = entity_data["supertype"];
    if (supertype == "hero") {
        return build_hero(game, entity_data);
    } else if (supertype == "mob") {
        return build_mob(game, entity_data);
    } else if (supertype == "corpse") {
        return build_corpse(game, entity_data);
    } else if (supertype == "undead") {
        return build_undead(game, entity_data);
    } else if (supertype == "essence") {
        return build_essence(game, entity_data);
    }
    throw std::runtime_error("Unknown entity supertype");
}

// TODO: make SkillBuilder
static std::shared_ptr<Skill> build_skill(const json& data) {
    // TODO: use more efficient approach
    using skill_factory = std::function<std::shared_ptr<Skill>()>;
    auto curse_factory = []() -> std::shared_ptr<Skill> {
        return std::make_shared<CurseSkill>();
    };
    auto desiccation_factory = []() -> std::shared_ptr<Skill> {
        return std::make_shared<DesiccationSkill>();
    };
    auto necromancy_factory = []() -> std::shared_ptr<Skill> {
        return std::make_shared<NecromancySkill>();
    };
    auto polymorph_factory = []() -> std::shared_ptr<Skill> {
        return std::make_shared<PolymorphSkill>();
    };
    auto wrath_factory = []() -> std::shared_ptr<Skill> {
        return std::make_shared<WrathSkill>();
    };

    static std::unordered_map<std::string, skill_factory> factories = {
        {"curse", curse_factory},
        {"desiccation", desiccation_factory},
        {"necromancy", necromancy_factory},
        {"polymorph", necromancy_factory},
        {"wrath", wrath_factory}};

    return factories.at(data["identifier"].template get<std::string>())();
}

std::shared_ptr<Entity> EntityBuilder::build_hero(Game* game,
                                                  const json& entity_data) {
    auto max_mana = entity_data["max_mana"].template get<int>();
    auto max_hp = entity_data["max_hp"].template get<int>();
    auto damage = entity_data["damage"].template get<int>();

    // TODO: make SkillSetBuilder
    auto skills_data = entity_data["skills"];
    auto skills = SkillSet();
    for (const auto& skill_data : skills_data["skills"]) {
        auto skill = build_skill(skill_data);
        auto level = skill_data["level"].template get<int>();
        skills.acquire_skill(skill);
        skills.upgrade_skill(skill, level);
    }

    auto hero = std::make_shared<Hero>(max_mana, skills, max_hp, damage);
    hero->init(entity_data);
    return hero;
}

std::shared_ptr<Entity> EntityBuilder::build_mob(Game* game,
                                                 const json& entity_data) {
    auto mob = game->plugin(entity_data["race"]).create_mob(entity_data);
    mob->init(entity_data);
    return mob;
}

std::shared_ptr<Entity> EntityBuilder::build_corpse(Game* game,
                                                    const json& entity_data) {
    throw std::runtime_error("build_corpse: not implemented yet");
}

std::shared_ptr<Entity> EntityBuilder::build_undead(Game* game,
                                                    const json& entity_data) {
    throw std::runtime_error("build_undead: not implemented yet");
}

std::shared_ptr<Entity> EntityBuilder::build_essence(Game* game,
                                                     const json& entity_data) {
    throw std::runtime_error("build_essence: not implemented yet");
}

}  // namespace rln
