#ifndef PLUGIN_MANAGER_HPP_
#define PLUGIN_MANAGER_HPP_

#include <functional>
#include <string>
#include <unordered_map>
#include "mob_plugin.hpp"

class PluginManager {
private:
    PluginManager() = default;

public:
    using ref_type = std::reference_wrapper<const rln::MobPlugin>;

    static PluginManager& get_instance();

    void add(const rln::MobPlugin& plugin);

    void remove(const std::string& name);

    const std::unordered_map<std::string, ref_type>& plugins() const;

private:
    std::unordered_map<std::string, ref_type> plugins_;
};

#endif  // !PLUGIN_MANAGER_HPP_
