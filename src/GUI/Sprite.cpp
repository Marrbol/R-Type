/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Sprite
*/

#include "GUI.hpp"

GUI::Sprite::Sprite(const SpriteData data) :
    m_data(data)
{
    if (m_texture.loadFromFile(data.path)) {
        _isTextureLoaded = true;
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, data.frame_width, data.frame_height));
}

void GUI::Sprite::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Sprite &GUI::Sprite::sprite()
{
    return m_sprite;
}

bool GUI::Sprite::isTextureLoaded() const
{
    return _isTextureLoaded;
}

GUI::Sprite::~Sprite()
{
}
