#ifndef DYNAMIC_LIBRARY_HPP_
#define DYNAMIC_LIBRARY_HPP_

#include <dlfcn.h>
#include <stdexcept>
#include <string>

class DynamicLibrary {
public:
    DynamicLibrary() noexcept;

    DynamicLibrary(const std::string& path);

    ~DynamicLibrary();

    DynamicLibrary(const DynamicLibrary& o) = delete;

    DynamicLibrary& operator=(const DynamicLibrary& o) = delete;

    DynamicLibrary(DynamicLibrary&& o);

    DynamicLibrary& operator=(DynamicLibrary&& o);

    void open(const std::string& path);

    void close() noexcept;

    template <class T>
    T symbol(const std::string& name) const requires std::is_pointer_v<T>;

private:
    void* lib;
};

template <class T>
T DynamicLibrary::symbol(const std::string& name) const requires std::is_pointer_v<T> {
    auto ret = reinterpret_cast<T>(dlsym(lib, name.c_str()));
    if (ret == nullptr) {
        throw std::runtime_error(dlerror());
    }
    return ret;
}

#endif
