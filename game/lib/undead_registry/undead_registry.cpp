#include "undead_registry.hpp"
#include <memory>
#include <string>
#include <utility>

namespace rln {

void UndeadRegistry::add(const std::string& identifier,
                         float multiplier,
                         UndeadFactory&& factory) {
    undead_factories_[identifier] = std::move(factory);
    undead_multipliers_[identifier] = multiplier;
}

std::shared_ptr<Undead> UndeadRegistry::build(const std::string& identifier,
                                              UndeadParams&& params) const {
    const auto& factory = undead_factories_.at(identifier);
    auto multiplier = undead_multipliers_.at(identifier);
    return factory(multiplier, std::move(params));
}

float UndeadRegistry::multiplier(const std::string& identifier) const {
    return undead_multipliers_.at(identifier);
}

}  // namespace rln
