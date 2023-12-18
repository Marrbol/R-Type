/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Sprite - a class that encapsulates everything related to a graphic sprite,
** such as its texture, its position, etc.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace GUI {

    // Stores the data of the texture file of a sprite
    struct SpriteData {
        const char *path;
        size_t frame_width;
        size_t frame_height;
        size_t frame_separation;
        size_t frames;
    };

    class Sprite {
    public:
        Sprite(const SpriteData data);
        void setPosition(float x, float y);
        sf::Sprite &sprite();
        bool isTextureLoaded() const;
        ~Sprite();

    private:
        sf::Sprite _sprite;
        sf::Texture _texture;
        SpriteData _data;
        bool _isTextureLoaded = false;
    };

}
