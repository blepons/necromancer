#pragma once

#include <nlohmann/json_fwd.hpp>

namespace rln {

using json = nlohmann::json;

class Serializable {
public:
    virtual ~Serializable() = default;

    virtual json serialize() = 0;
};

}  // namespace rln
