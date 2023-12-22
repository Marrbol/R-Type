/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Component
*/

#pragma once

#include "GUI.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

namespace component {

    class Position {
    public:
        Position(float x, float y) : x(x), y(y) {};
        ~Position() = default;
        float x;
        float y;
    };

    class Velocity {
    public:
        Velocity(float x, float y) : x(x), y(y) {};
        ~Velocity() = default;
        float x;
        float y;
    };

    class Drawable {
    public:
        Drawable(const std::string &path, size_t draw_order = 0) : path(path), draw_order(draw_order) {
            texture = std::make_shared<sf::Texture>();
            texture->loadFromFile(path);
            sprite = std::make_shared<sf::Sprite>();
            sprite->setTexture(*texture);
        };
        ~Drawable() = default;
        std::string path;
        std::shared_ptr<sf::Sprite> sprite;
        size_t draw_order;
    private:
        std::shared_ptr<sf::Texture> texture;
    };

    class Controllable {
    public:
        Controllable(float speed, float slow) : speed(speed), slow(slow) {};
        ~Controllable() = default;
        float speed;
        float slow;
    };

    class HitBox {
    public:
        HitBox(float width, float height) : width(width), height(height) {};
        ~HitBox() = default;
        float width;
        float height;
    };

    class BoundsLimit {
    public:
        BoundsLimit(float minX, float minY, float maxX, float maxY) : minX(minX), minY(minY), maxX(maxX), maxY(maxY) {};
        ~BoundsLimit() = default;
        float minX;
        float minY;
        float maxX;
        float maxY;
    };

    class Respawnable {
    public:
        Respawnable(float x, float y) : x(x), y(y) {};
        ~Respawnable() = default;
        float x;
        float y;
    };

}
