#pragma once

#include <memory>
namespace rln {

class Entity;

class Attack {
public:
    Attack(int range);

    void perform(std::shared_ptr<Entity> source,
                 std::shared_ptr<Entity> target);

    bool ranged() const;

    static Attack melee();

private:
    int range_;
};

}  // namespace rln
