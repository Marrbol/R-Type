/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#include "ECS/SystemHandler.hpp"
#include "GUI.hpp"

// Constructors ---------------------------------------------------------------

SystemHandler::SystemHandler(Registry &registry, GUI::GUI &gui):
    m_registry(registry),
    m_gui(gui)
{
}

SystemHandler::SystemHandler(Registry &registry):
    m_registry(registry)
{
}

// Main loop ------------------------------------------------------------------

void SystemHandler::run()
{
    sparse_array<component::Position> &positions = m_registry.get_components<component::Position>();
    sparse_array<component::Velocity> &velocities = m_registry.get_components<component::Velocity>();
    sparse_array<component::Controllable> &controllables = m_registry.get_components<component::Controllable>();
    sparse_array<component::Drawable> &drawables = m_registry.get_components<component::Drawable>();

    while (true) {
        GUI::GUI& gui = m_gui.value().get();
        position_system(positions, velocities, controllables);
        control_system(controllables, velocities, gui);
        draw_system(positions, drawables, gui);
    }
}

// Systems --------------------------------------------------------------------

void SystemHandler::position_system(sparse_array<component::Position> &positions,
    sparse_array<component::Velocity> &velocities,
    sparse_array<component::Controllable> &controllables)
{

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &cont = controllables[i];
        if (pos && vel) {
            pos.value().x += vel.value().x;
            pos.value().y += vel.value().y;
            if (cont) {
                vel.value().x *= cont.value().slow;
                vel.value().y *= cont.value().slow;
            }
        }
    }
}

void SystemHandler::control_system(sparse_array<component::Controllable> &controllables,
    sparse_array<component::Velocity> &velocities, GUI::GUI &gui)
{

    std::vector<GUI::Input> inputs = gui.getInputs();
    for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
        auto &cont = controllables[i];
        auto &vel = velocities[i];
        if (cont && vel) {
            for (auto input : inputs) {
                switch (input) {
                    case GUI::Input::UP:
                        vel.value().y -= cont.value().speed;
                        break;
                    case GUI::Input::DOWN:
                        vel.value().y += cont.value().speed;
                        break;
                    case GUI::Input::LEFT:
                        vel.value().x -= cont.value().speed;
                        break;
                    case GUI::Input::RIGHT:
                        vel.value().x += cont.value().speed;
                        break;
                    case GUI::Input::SHOOT:
                        break;
                    case GUI::Input::NONE:
                    default:
                        break;
                }
            }
        }
    }
}

void SystemHandler::draw_system(sparse_array<component::Position> &positions,
    sparse_array<component::Drawable> &drawables, GUI::GUI &gui)
{
    gui.clear();
    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto &pos = positions[i];
        auto &draw = drawables[i];
        if (pos && draw) {
            gui.draw(pos.value().x, pos.value().y, draw.value().appearance);
        }
    }
    gui.display();
}
