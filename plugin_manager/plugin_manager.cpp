#include "plugin_manager.hpp"
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void PluginManager::scan(const std::string& path,
                         const std::string& extension,
                         const std::string& symbol) {
    fs::path dir_path(path);
    for (auto& file : fs::directory_iterator(dir_path)) {
        if ((file.is_regular_file() || file.is_symlink()) &&
            file.path().extension() == extension) {
            DynamicLibrary lib(file.path());
            const rln::MobPlugin& plug =
                lib.symbol<rln::MobPlugin& (*)()>(symbol)();
            plugins_.emplace_back(std::move(lib), std::ref(plug));
        }
    }
}

void PluginManager::clear() {
    plugins_.clear();
}

const std::vector<PluginManager::PluginInfo>& PluginManager::plugins() const {
    return plugins_;
}
