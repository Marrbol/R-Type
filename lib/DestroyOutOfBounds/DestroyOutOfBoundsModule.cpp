/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Physics
*/

#include "DestroyOutOfBoundsModule.hpp"

void DestroyOutOfBounds::run(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &positions = registry.get_components<component::Position>();
    auto &bounds = registry.get_components<component::BoundsLimit>();

    for (size_t i = 0; i < positions.size() || i < bounds.size(); i++) {
        auto &pos = positions[i];
        auto &bound = bounds[i];

        /*if (pos && bound) {
            if (pos->x < 0 || pos->y < 0 || pos->x > gui.get_width() || pos->y > gui.get_height()) {
                registry.kill_entity(registry.entity_from_index(i));
            }
        }*/
    }
}
