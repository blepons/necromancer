#pragma once

#include <string>

namespace rln {

class Faction {
public:
    static constexpr std::string hero = "hero";

    static constexpr std::string none = "none";

    static constexpr std::string non_entity = "static";

    explicit Faction(std::string faction);

    bool hostile(const Faction& other) const;

    void set(std::string faction);

    std::string string() const;

private:
    std::string faction_;
};

}  // namespace rln
