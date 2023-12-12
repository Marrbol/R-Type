/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Component
*/

#pragma once

#include "GUI.hpp"

namespace component {

    struct Position
    {
        float x;
        float y;
    };

    struct Velocity
    {
        float x;
        float y;
    };

    struct Drawable
    {
        GUI::Appearance appearance;
    };

    struct Controllable
    {
        float speed;
        float slow;
        float shoot_cooldown;
    };

}
