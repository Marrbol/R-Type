/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Sprite
*/

#include "GUI.hpp"

GUI::Sprite::Sprite(const SpriteData data) :
    _data(data)
{
    if (_texture.loadFromFile(data.path)) {
        _isTextureLoaded = true;
    }
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, data.frame_width, data.frame_height));
}

void GUI::Sprite::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}

sf::Sprite &GUI::Sprite::sprite()
{
    return _sprite;
}

bool GUI::Sprite::isTextureLoaded() const
{
    return _isTextureLoaded;
}

GUI::Sprite::~Sprite()
{
}
