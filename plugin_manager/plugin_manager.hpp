#ifndef PLUGIN_MANAGER_HPP_
#define PLUGIN_MANAGER_HPP_

#include <dlfcn.h>
#include <vector>

#include "dynamic_library.hpp"
#include "mob_plugin.hpp"

class PluginManager {
public:
    struct PluginInfo {
        DynamicLibrary library;
        std::reference_wrapper<const rln::MobPlugin> plugin;
    };

    void scan(const std::string& path,
              const std::string& extension,
              const std::string& symbol);

    void clear();

    const std::vector<PluginInfo>& plugins() const;

private:
    std::vector<PluginInfo> plugins_;
};

#endif  // !PLUGIN_MANAGER_HPP_
