/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#include "ECS/SystemHandler.hpp"
#include "GUI.hpp"

// Forward declarations -------------------------------------------------------

void position_system(
    sparse_array<component::Position> &positions,
    sparse_array<component::Velocity> &velocities,
    sparse_array<component::Controllable> &controllables);

void control_system(GUI::IGUI &gui, sparse_array<component::Controllable> &controllables,
    sparse_array<component::Velocity> &velocities);

void draw_system(GUI::IGUI &gui, sparse_array<component::Position> &positions,
    sparse_array<component::Drawable> &drawables);

// Constructors ---------------------------------------------------------------

SystemHandler::SystemHandler(Registry &registry, GUI::IGUI &gui):
    m_registry(registry),
    m_gui(gui)
{
}

SystemHandler::SystemHandler(Registry &registry):
    m_registry(registry)
{
}

// Methods --------------------------------------------------------------------

void SystemHandler::run()
{
    sparse_array<component::Position> &positions = m_registry.get_components<component::Position>();
    sparse_array<component::Velocity> &velocities = m_registry.get_components<component::Velocity>();
    sparse_array<component::Controllable> &controllables = m_registry.get_components<component::Controllable>();
    sparse_array<component::Drawable> &drawables = m_registry.get_components<component::Drawable>();
    sparse_array<component::HitBox> &hitboxes = m_registry.get_components<component::HitBox>();

    if (m_gui) {
        GUI::IGUI &gui = m_gui.value().get();
        while (true) {
            position_system(positions, velocities, controllables);
            control_system(gui, controllables, velocities);
            draw_system(gui, positions, drawables);
        }
    } else {
        while (true) {
            position_system(positions, velocities, controllables);
        }
    }
}

// Systems --------------------------------------------------------------------

void position_system(
    sparse_array<component::Position> &positions,
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

void control_system(GUI::IGUI &gui, sparse_array<component::Controllable> &controllables,
    sparse_array<component::Velocity> &velocities)
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

void draw_system(GUI::IGUI &gui, sparse_array<component::Position> &positions,
    sparse_array<component::Drawable> &drawables)
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
