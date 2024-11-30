#ifndef LIBRARY_MANAGER_HPP_
#define LIBRARY_MANAGER_HPP_

#include <dlfcn.h>
#include <functional>
#include <string>
#include <vector>
#include "dynamic_library.hpp"
#include "mob_plugin.hpp"

class LibraryManager {
public:
    struct PluginInfo {
        DynamicLibrary library;
        std::reference_wrapper<const rln::MobPlugin> plugin;
    };

    void scan(const std::string& path,
              const std::string& extension,
              const std::string& symbol);

private:
    std::vector<PluginInfo> plugins_;
};

#endif  // !LIBRARY_MANAGER_HPP_
