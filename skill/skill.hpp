#pragma once

#include <string>

namespace rln {

class Hero;

class Skill {
public:
    virtual ~Skill() = default;

    int max_level() const;

    int level(Hero* hero) const;

    std::string identifier() const;

private:
    std::string identifier_;
};

}  // namespace rln
