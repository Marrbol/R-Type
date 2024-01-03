/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-oceane.krull
** File description:
** CollisionModule
*/

#include <iostream>
#include "CollisionModule.hpp"

void Collision::run(ECS::Core &c)
{
    // print a message if there is a collision
    auto &registry = c.get_registry();
    auto &positions = registry.get_components<component::Position>();
    auto &hitboxes = registry.get_components<component::HitBox>();

    for (size_t i = 0; i < positions.size() || i < hitboxes.size(); i++) {
        auto &pos = positions[i];
        auto &hit = hitboxes[i];
        for (size_t j = i + 1; j < positions.size() || j < hitboxes.size(); j++) {
            auto &pos2 = positions[j];
            auto &hit2 = hitboxes[j];
            if (pos->x + hit->width >= pos2->x && pos->x <= pos2->x + hit2->width && pos->y + hit->height >= pos2->y && pos->y <= pos2->y + hit2->height) {
                std::cout << "Collision !" << std::endl;
            }
        }
    }
}