#include "plugin_keeper.hpp"
#include "plugin_manager.hpp"

PluginKeeper::PluginKeeper(const rln::MobPlugin& plugin) : plugin_(plugin) {
    PluginManager::get_instance().add(plugin);
}

PluginKeeper::~PluginKeeper() {
    PluginManager::get_instance().remove(plugin_.name());
}
