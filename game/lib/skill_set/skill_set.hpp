#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "serializable.hpp"

namespace rln {

class Skill;

class SkillSet : public Serializable {
public:
    SkillSet() = default;

    json serialize() override;

    int level(std::shared_ptr<Skill> skill) const;

    void acquire_skill(std::shared_ptr<Skill> skill);

    void upgrade_skill(std::shared_ptr<Skill> skill, int points);

    std::pair<std::shared_ptr<Skill>, int>& get(std::string identifier);

    std::vector<std::shared_ptr<Skill>> skills();

    std::vector<std::shared_ptr<Skill>> castable();

private:
    std::unordered_map<std::string, std::pair<std::shared_ptr<Skill>, int>>
        level_map_;
};

}  // namespace rln
