#pragma once

#include <unordered_map>
#include <vector>

namespace rln {

class Skill;

class SkillSet {
public:
    SkillSet() = default;

    int level(Skill* skill) const;

    void upgrade_skill(Skill* skill, int points);

    std::vector<Skill*> skills();

    std::vector<Skill*> castable();

private:
    std::unordered_map<Skill*, int> level_map_;
};

}  // namespace rln
