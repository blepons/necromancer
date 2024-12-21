#pragma once

#include <memory>
#include <string>
#include "serializable.hpp"

namespace rln {

class Hero;

class Skill : public Serializable, public std::enable_shared_from_this<Skill> {
public:
    Skill(std::string identifier, int max_level);

    virtual ~Skill() = default;

    json serialize() override;

    int max_level() const;

    int level(std::shared_ptr<Hero> hero);

    std::string identifier() const;

private:
    std::string identifier_;
    int max_level_;
};

}  // namespace rln
