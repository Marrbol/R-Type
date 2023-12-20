/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Component
*/

#pragma once

#include "GUI.hpp"

namespace component {

    struct Position {
        float x;
        float y;
    };

    struct Velocity
    {
        float x;
        float y;
    };

    struct Drawable // Check if this is a good idea
    {
        sf::Sprite sprite;
        sf::Texture texture;
        size_t draw_order;
    };

    struct Controllable
    {
        float speed;
        float slow;
        float shoot_cooldown;
    };

    struct HitBox
    {
        float x;
        float y;
    };

}
