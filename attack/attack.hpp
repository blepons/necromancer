#pragma once

#include <memory>
namespace rln {

class Entity;

class Attack {
public:
    Attack(int damage, int range);

    void perform(std::shared_ptr<Entity> source,
                 std::shared_ptr<Entity> target);

    bool ranged() const;

private:
    int damage_;
    int range_;
};

}  // namespace rln
