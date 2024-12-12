#pragma once

#include <memory>
#include "serializable.hpp"

namespace rln {

class Entity;

class Attack : public Serializable {
public:
    Attack(int range);

    json serialize() override;

    void perform(std::shared_ptr<Entity> source,
                 std::shared_ptr<Entity> target);

    bool ranged() const;

    static Attack melee();

private:
    int range_;
};

}  // namespace rln
