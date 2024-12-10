#include "faction.hpp"
#include <string>

namespace rln {

Faction::Faction(std::string faction) : faction_(std::move(faction)) {}

bool Faction::hostile(const Faction& other) const {
    if (other.faction_ == non_entity) {
        return false;
    }
    if (faction_ == none) {
        return true;
    }
    return faction_ != other.faction_;
}

std::string Faction::string() const {
    return faction_;
}

}  // namespace rln
