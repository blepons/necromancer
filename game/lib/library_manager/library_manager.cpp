#include "library_manager.hpp"
#include <filesystem>

namespace fs = std::filesystem;

void LibraryManager::scan(const std::string& path,
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
