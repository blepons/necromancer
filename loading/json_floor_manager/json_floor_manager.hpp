#pragma once

#include <memory>
#include <string>
#include <vector>
#include "floor_manager.hpp"
#include "stage.hpp"

namespace rln {

class JsonFloorManager : public FloorManager {
public:
    JsonFloorManager(const std::vector<std::string>& stage_paths);

    Stage* stage() override;

    void load_next_floor(Game* game) override;

    void unload_current_floor() override;

private:
    std::vector<std::string> stage_paths_;
    int current_stage_index_;
    std::unique_ptr<Stage> stage_;

    int index() const;

    void index(int new_index);

    void next_index();

    // TODO: replace with enum and store it somewhere
    static constexpr int index_not_loaded_yet = -1;
    static constexpr int index_finished = -2;
};

}  // namespace rln
