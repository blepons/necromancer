#pragma once

#include <cstddef>
#include <queue>
#include <utility>

namespace rln {

template <class T>
struct cost_wrapper {
    T value;
    std::size_t cost;

    T operator*() const { return std::move(value); }
};

template <class T>
inline auto operator<(const cost_wrapper<T>& lhs, const cost_wrapper<T>& rhs) {
    return lhs.cost < rhs.cost;
}

template <class T>
using cost_priority_queue = std::priority_queue<cost_wrapper<T>>;

}  // namespace rln
