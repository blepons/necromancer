#include "skill_set.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <ranges>
#include <string>
#include <utility>
#include <vector>
#include "skill.hpp"

namespace rln {

json SkillSet::serialize() {
    json::array_t skills;
    for (const auto& [_, pair] : level_map_) {
        const auto& [skill, level] = pair;
        json skill_data = skill->serialize();
        skill_data.update({{"level", level}});
        skills.emplace_back(skill_data);
    }
    return {{"skills", skills}};
}

int SkillSet::level(std::shared_ptr<Skill> skill) const {
    if (auto it = level_map_.find(skill->identifier());
        it != level_map_.end()) {
        return it->second.second;
    }
    return 0;
}

void SkillSet::acquire_skill(std::shared_ptr<Skill> skill) {
    if (auto it = level_map_.find(skill->identifier());
        it != level_map_.end()) {
        // throw: skill already acquired
    }
    level_map_[skill->identifier()] = {skill, 0};
}

void SkillSet::upgrade_skill(std::shared_ptr<Skill> skill, int points) {
    if (auto it = level_map_.find(skill->identifier());
        it != level_map_.end()) {
        it->second.second += points;
    }
    // throw: skill not found
}

std::pair<std::shared_ptr<Skill>, int>& SkillSet::get(std::string identifier) {
    return level_map_.at(identifier);
}

std::vector<std::shared_ptr<Skill>> SkillSet::skills() {
    auto rg = level_map_ | std::views::values | std::views::keys;
    return std::vector<std::shared_ptr<Skill>>(rg.begin(), rg.end());
}

std::vector<std::shared_ptr<Skill>> SkillSet::castable() {
    auto rg = level_map_ | std::views::filter([](const auto& v) {
                  return std::get<1>(v).second > 0;
              }) |
              std::views::values | std::views::keys;
    return std::vector<std::shared_ptr<Skill>>(rg.begin(), rg.end());
}

}  // namespace rln
