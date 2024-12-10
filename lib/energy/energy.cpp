#include "energy.hpp"
#include <cstddef>

namespace rln {

bool Energy::can_take_turn() const {
    return action_cost <= amount_;
}

bool Energy::will_take_turn(std::size_t speed_index) const {
    return action_cost <= amount_ + speed_gains[speed_index];
}

void Energy::gain(std::size_t speed_index) {
    amount_ += speed_gains[speed_index];
}

void Energy::spend() {
    if (amount_ <= action_cost) {
        // throw?
    }
    amount_ -= action_cost;
}

int Energy::amount() {
    return amount_;
}

}  // namespace rln
