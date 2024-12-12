#include "skill_set.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <ranges>
#include <vector>
#include "skill.hpp"

namespace rln {

json SkillSet::serialize() {
    json::array_t skills;
    for (const auto& [skill, level] : level_map_) {
        json skill_data = skill->serialize();
        skill_data.update({{"level", level}});
        skills.emplace_back(skill_data);
    }
    return {{"skills", skills}};
}

int SkillSet::level(std::shared_ptr<Skill> skill) const {
    if (auto it = level_map_.find(skill); it != level_map_.end()) {
        return it->second;
    }
    return 0;
}

void SkillSet::acquire_skill(std::shared_ptr<Skill> skill) {
    if (auto it = level_map_.find(skill); it != level_map_.end()) {
        // throw: skill already acquired
    }
    level_map_[skill] = 0;
}

void SkillSet::upgrade_skill(std::shared_ptr<Skill> skill, int points) {
    if (auto it = level_map_.find(skill); it != level_map_.end()) {
        it->second += points;
    }
    // throw: skill not found
}

std::vector<std::shared_ptr<Skill>> SkillSet::skills() {
    auto rg = level_map_ | std::views::keys;
    return std::vector<std::shared_ptr<Skill>>(rg.begin(), rg.end());
}

std::vector<std::shared_ptr<Skill>> SkillSet::castable() {
    auto rg =
        level_map_ |
        std::views::filter([](const auto& v) { return std::get<1>(v) > 0; }) |
        std::views::keys;
    return std::vector<std::shared_ptr<Skill>>(rg.begin(), rg.end());
}

}  // namespace rln
