#include "plugin_manager.hpp"
#include <string>
#include "mob_plugin.hpp"

void PluginManager::add(const rln::MobPlugin& plugin) {
    plugins_.try_emplace(plugin.name(), plugin);
}

void PluginManager::remove(const std::string& name) {
    plugins_.erase(name);
}

const std::unordered_map<std::string, PluginManager::ref_type>&
PluginManager::plugins() const {
    return plugins_;
}

PluginManager& PluginManager::get_instance() {
    static PluginManager manager;
    return manager;
}
