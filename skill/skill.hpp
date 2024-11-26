#pragma once

#include <memory>
#include <string>

namespace rln {

class Hero;

class Skill {
public:
    Skill(std::string identifier, int max_level);

    virtual ~Skill() = default;

    int max_level() const;

    int level(std::shared_ptr<Hero> hero);

    std::string identifier() const;

private:
    std::string identifier_;
    int max_level_;
};

}  // namespace rln
