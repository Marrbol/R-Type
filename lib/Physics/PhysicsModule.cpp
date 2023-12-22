/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Physics
*/

#include "PhysicsModule.hpp"

void Physics::run(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &positions = registry.get_components<component::Position>();
    auto &velocities = registry.get_components<component::Velocity>();
    auto &controllables = registry.get_components<component::Controllable>();
    auto &hitboxes = registry.get_components<component::HitBox>();

    for (size_t i = 0; i < positions.size() || i < velocities.size() || i < controllables.size() || i < hitboxes.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &cont = controllables[i];
        auto &hit = hitboxes[i];
        size_t limitX = gui.get_width() - hit->width;
        size_t limitY = gui.get_height() - hit->height;

        if (pos && vel) {
            pos->x += vel->x;
            pos->y += vel->y;
            if (cont) {
                if (pos->x < 0)
                    pos->x = 0;
                if (pos->y < 0)
                    pos->y = 0;
                if (pos->x > limitX)
                    pos->x = limitX;
                if (pos->y > limitY)
                    pos->y = limitY;
                vel->x *= cont->slow;
                vel->y *= cont->slow;
            }
        }
    }
}
