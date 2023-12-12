/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#pragma once

#include <variant>

#include "Registry.hpp"
#include "Component.hpp"
#include "GUI.hpp"

class SystemHandler {
public:
    SystemHandler(Registry &registry, GUI::GUI &gui);
    SystemHandler(Registry &registry);
    ~SystemHandler() = default;
    void run();

private:

    void position_system(sparse_array<component::Position> &positions,
        sparse_array<component::Velocity> &velocities,
        sparse_array<component::Controllable> &controllables);
    void control_system(sparse_array<component::Controllable> &controllables,
        sparse_array<component::Velocity> &velocities, GUI::GUI &gui);
    void draw_system(sparse_array<component::Position> &positions,
        sparse_array<component::Drawable> &drawables, GUI::GUI &gui);

    Registry &m_registry;
    std::optional<std::reference_wrapper<GUI::GUI>> m_gui;
};
