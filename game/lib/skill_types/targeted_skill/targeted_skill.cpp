#include "targeted_skill.hpp"
#include <string>
#include <utility>
#include "usable_skill.hpp"

namespace rln {

TargetedSkill::TargetedSkill(std::string identifier, int max_level)
    : UsableSkill(std::move(identifier), max_level) {}

}  // namespace rln
