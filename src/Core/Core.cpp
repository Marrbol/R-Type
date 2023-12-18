/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Core
*/

#include "Core.hpp"

void physics_system(ECS::Core &c);
void render_system(ECS::Core &c);
void input_system(ECS::Core &c);

// Constructors ---------------------------------------------------------------

ECS::SystemHandler::SystemHandler(ECS::Core &core): _core(core)
{
    add_system(&physics_system);
    add_system(&render_system);
    add_system(&input_system);
}

ECS::SystemHandler::~SystemHandler()
{
}

ECS::Core::Core(GUI::IGUI &gui): _gui(gui)
{
    auto &registry = get_registry();

    registry.register_component<component::Position>();
    registry.register_component<component::Velocity>();
    registry.register_component<component::Drawable>();
    registry.register_component<component::Controllable>();
    registry.register_component<component::HitBox>();

    entity e = registry.spawn_entity();
    registry.add_component(e, component::Position{0, 0});
    registry.add_component(e, component::Velocity{0, 0});
    registry.add_component(e, component::Drawable{GUI::Appearance::PLAYER_IDLE});
    registry.add_component(e, component::Controllable{10, 0.9});
    registry.add_component(e, component::HitBox{100, 100});
}

ECS::Core::~Core()
{
}

// Functions ------------------------------------------------------------------

void physics_system(ECS::Core &c)
{
    auto &registry = c.get_registry();

    auto &positions = registry.get_components<component::Position>();
    auto &velocities = registry.get_components<component::Velocity>();
    auto &controllables = registry.get_components<component::Controllable>();

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

void render_system(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &positions = registry.get_components<component::Position>();
    auto &drawables = registry.get_components<component::Drawable>();

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

void input_system(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &velocities = registry.get_components<component::Velocity>();
    auto &controllables = registry.get_components<component::Controllable>();

    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto &vel = velocities[i];
        auto &cont = controllables[i];

        if (vel && cont) {
            std::vector<GUI::Input> inputs = gui.getInputs();
            for (auto input : inputs) {
                if (input == GUI::Input::UP)
                    vel.value().y -= cont.value().speed;
                if (input == GUI::Input::DOWN)
                    vel.value().y += cont.value().speed;
                if (input == GUI::Input::LEFT)
                    vel.value().x -= cont.value().speed;
                if (input == GUI::Input::RIGHT)
                    vel.value().x += cont.value().speed;
            }
        }
    }
}
