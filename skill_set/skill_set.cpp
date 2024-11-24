#include "skill_set.hpp"
#include <ranges>
#include <vector>

namespace rln {

int SkillSet::level(Skill* skill) const {
    if (auto it = level_map_.find(skill); it != level_map_.end()) {
        return it->second;
    }
    return 0;
}

void SkillSet::upgrade_skill(Skill* skill, int points) {
    level_map_[skill] += points;
}

std::vector<Skill*> SkillSet::skills() {
    auto rg = level_map_ | std::views::keys;
    return std::vector<Skill*>(rg.begin(), rg.end());
}

std::vector<Skill*> SkillSet::castable() {
    auto rg =
        level_map_ |
        std::views::filter([](const auto& v) { return std::get<1>(v) > 0; }) |
        std::views::keys;
    return std::vector<Skill*>(rg.begin(), rg.end());
}

}  // namespace rln
