#pragma once

#include <string>

namespace rln {

class Faction {
public:
    static constexpr std::string_view hero = "hero";

    static constexpr std::string_view none = "none";

    static constexpr std::string_view non_entity = "static";

    explicit Faction(std::string_view faction);

    bool hostile(const Faction& other) const;

    void set(std::string_view faction);

    std::string string() const;

private:
    std::string faction_;
};

}  // namespace rln
