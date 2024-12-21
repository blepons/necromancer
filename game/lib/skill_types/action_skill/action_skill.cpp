#include "action_skill.hpp"
#include <string>
#include <utility>
#include "usable_skill.hpp"

namespace rln {

ActionSkill::ActionSkill(std::string identifier, int max_level)
    : UsableSkill(std::move(identifier), max_level) {}

}  // namespace rln
