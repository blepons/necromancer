#pragma once

#include <bitset>

class Passability {
public:
    Passability(unsigned mask) : bitmask_(mask) {}

    Passability(std::bitset<2> mask) : bitmask_(mask) {}

    static Passability none() { return Passability(0); }

    static Passability walk() { return Passability(1); }

    static Passability door() { return Passability(2); }

    static Passability door_or_walk();

    static Passability all();

    bool overlaps(const Passability& other) const;

    Passability& operator|=(const Passability& other) {
        bitmask_ |= other.bitmask_;
        return *this;
    }

    Passability& operator&=(const Passability& other) {
        bitmask_ &= other.bitmask_;
        return *this;
    }

    std::bitset<2> bitmask() const { return bitmask_; }

private:
    std::bitset<2> bitmask_;
};

inline Passability operator|(const Passability& lhs, const Passability& rhs) {
    Passability tmp(lhs);
    tmp |= rhs;
    return tmp;
}

inline Passability operator&(const Passability& lhs, const Passability& rhs) {
    Passability tmp(lhs);
    tmp &= rhs;
    return tmp;
}

inline Passability Passability::door_or_walk() {
    return walk() | door();
}

inline Passability Passability::all() {
    return walk() | door();
}

inline bool Passability::overlaps(const Passability& other) const {
    return (bitmask() & other.bitmask()) != none().bitmask();
}
