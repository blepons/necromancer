#include "undead_registry.hpp"
#include <memory>
#include <string>
#include <utility>

namespace rln {

void UndeadRegistry::add(const std::string& identifier,
                         UndeadFactory&& factory) {
    undead_factories_[identifier] = std::move(factory);
}

std::shared_ptr<Undead> UndeadRegistry::build(const std::string& identifier,
                                              UndeadParams&& params) const {
    const auto& factory = undead_factories_.at(identifier);
    return factory(std::move(params));
}

}  // namespace rln
