#pragma once

#include <memory>
#include "entity.hpp"

namespace rln {

class EntityBuilder {
public:
    static std::shared_ptr<Entity> build(Game* game, const json& entity_data);

private:
    static std::shared_ptr<Entity> build_hero(Game* game,
                                              const json& entity_data);

    static std::shared_ptr<Entity> build_mob(Game* game,
                                             const json& entity_data);

    static std::shared_ptr<Entity> build_corpse(Game* game,
                                                const json& entity_data);

    static std::shared_ptr<Entity> build_undead(Game* game,
                                                const json& entity_data);

    static std::shared_ptr<Entity> build_essence(Game* game,
                                                 const json& entity_data);
};

}  // namespace rln
