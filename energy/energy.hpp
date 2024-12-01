#pragma once

#include <array>
#include <cstddef>

namespace rln {

class Energy {
public:
    static constexpr int action_cost = 120;

    static constexpr std::size_t lowest_speed = 0;
    static constexpr std::size_t normal_speed = 4;
    static constexpr std::size_t highest_speed = 8;

    static constexpr std::array speed_gains = {12, 15,  20,  30, 60,
                                               80, 120, 180, 240};

    Energy() = default;

    bool can_take_turn() const;

    bool will_take_turn(std::size_t speed_index) const;

    void gain(std::size_t speed_index);

    void spend();

private:
    int amount_ = 0;
};

}  // namespace rln
