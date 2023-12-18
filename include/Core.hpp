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

namespace ECS {

    class Core {
    public:
        Core(GUI::IGUI &gui);
        ~Core();

        GUI::IGUI &get_gui() { return _gui; }
        Registry &get_registry() { return _registry; }
    private:
        GUI::IGUI &_gui;
        Registry _registry;
    };

    class SystemHandler {
    public:
        SystemHandler(Core &core);
        ~SystemHandler();
        void add_system(std::function<void(Core &)> system) { _systems.push_back(system); }
        void run() { for (auto &system : _systems) system(_core); }
    private:
        std::vector<std::function<void(Core &)>> _systems;
        Core &_core;
    };

    class RuntimeException : public std::exception {
    public:
        RuntimeException(const std::string &message) : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }
    private:
        std::string _message;
    };

}
