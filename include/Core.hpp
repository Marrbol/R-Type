/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Core
*/

#pragma once

#include "Core/Registry.hpp"
#include "Core/Component.hpp"

#include "GUI.hpp"

#ifdef _WIN32
    #include <Windows.h>
    #define LIB_HANDLE HINSTANCE
    #define LIB_LOAD(path) LoadLibrary(path)
    #define LIB_GETSYM(handle, name) GetProcAddress(handle, name)
    #define LIB_CLOSE(handle) FreeLibrary(handle)
    #define LIB_ERROR() GetLastError()
    #define LIB_EXT ".dll"
#else
    #include <dlfcn.h>
    #define LIB_HANDLE void *
    #define LIB_LOAD(path) dlopen(path, RTLD_LAZY)
    #define LIB_GETSYM(handle, name) dlsym(handle, name)
    #define LIB_CLOSE(handle) dlclose(handle)
    #define LIB_ERROR() dlerror()
    #define LIB_EXT ".so"
#endif

namespace ECS {

    class RuntimeException : public std::exception {
    public:
        RuntimeException(const std::string &message) : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }
    private:
        std::string _message;
    };

    class Core {
    public:
        Core(GUI::IGUI &gui);
        ~Core();

        GUI::IGUI &get_gui();
        Registry &get_registry();
    private:
        GUI::IGUI &_gui;
        Registry _registry;
    };

    class SystemHandler {
        using System = std::function<void(ECS::Core &)>;
    public:
        SystemHandler(Core &core);
        ~SystemHandler();
        // void load_system(const std::string &path);
        void load_system(System system);
        void run();
    private:
        std::vector<System> _systems;
        Core &_core;
        std::vector<LIB_HANDLE> _handles;
    };

}
