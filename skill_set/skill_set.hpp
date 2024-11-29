#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

namespace rln {

class Skill;

class SkillSet {
public:
    SkillSet() = default;

    int level(std::shared_ptr<Skill> skill) const;

    void acquire_skill(std::shared_ptr<Skill> skill);

    void upgrade_skill(std::shared_ptr<Skill> skill, int points);

    std::vector<std::shared_ptr<Skill>> skills();

    std::vector<std::shared_ptr<Skill>> castable();

private:
    std::unordered_map<std::shared_ptr<Skill>, int> level_map_;
};

}  // namespace rln
