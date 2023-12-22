/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Physics
*/

#include "ControlModule.hpp"

void Control::run(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &velocities = registry.get_components<component::Velocity>();
    auto &controllables = registry.get_components<component::Controllable>();
    auto &hitboxes = registry.get_components<component::HitBox>();
    auto &positions = registry.get_components<component::Position>();

    for (size_t i = 0; i < velocities.size() || i < controllables.size() || i < hitboxes.size() || i < positions.size(); i++) {
        auto &vel = velocities[i];
        auto &cont = controllables[i];
        auto &hit = hitboxes[i];
        auto &pos = positions[i];

        if (vel && cont && hit && pos) {
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
                if (input == GUI::Input::SPACE) {
                    entity e = registry.spawn_entity();
                    registry.add_component(e, component::Position(pos->x + hit->width, pos->y + hit->height / 2));
                    registry.add_component(e, component::Velocity(20, 0));
                    registry.add_component(e, component::HitBox(70, 70));
                    registry.add_component(e, component::Drawable("../assets/images/bullet.png"));
                    // registry.add_component(e, component::BoundsLimit(0, 0, gui.get_width(), gui.get_height()));
                }
            }
        }
    }
}
