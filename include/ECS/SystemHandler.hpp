/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#pragma once

#include "Registry.hpp"
#include "Component.hpp"
#include "GUI.hpp"

class SystemHandler {
public:
    SystemHandler(Registry &registry, GUI::IGUI &gui);
    SystemHandler(Registry &registry);
    ~SystemHandler() = default;
    void run();

private:

    Registry &m_registry;
    std::optional<std::reference_wrapper<GUI::IGUI>> m_gui;

};
