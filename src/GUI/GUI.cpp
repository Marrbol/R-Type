/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GUI
*/

#include "GUI.hpp"

GUI::GUI::GUI()
{
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "R-Type");
    m_window->setFramerateLimit(60);
    m_window->setKeyRepeatEnabled(true);
    m_event = new sf::Event;

    loadSprites();
}

void GUI::GUI::loadSprites()
{
    for (auto appearance : m_appearances) {
        m_sprites[appearance] = new Sprite(m_sprites_data[appearance]);
    }
}

void GUI::GUI::draw(float x, float y, Appearance appearance)
{
    m_sprites[appearance]->setPosition(x, y);
    m_window->draw(m_sprites[appearance]->sprite());
}

void GUI::GUI::clear()
{
    m_window->clear();
}

void GUI::GUI::display()
{
    m_window->display();
}

std::vector<GUI::Input> GUI::GUI::getInputs()
{
    std::vector<Input> inputs;

    while (m_window->pollEvent(*m_event)) {
        if (m_event->type == sf::Event::Closed)
            m_window->close();
        if (!m_window->hasFocus())
            continue;
        if (m_event->type == sf::Event::KeyPressed) {
            if (m_event->key.code == sf::Keyboard::Up)
                inputs.push_back(Input::UP);
            if (m_event->key.code == sf::Keyboard::Down)
                inputs.push_back(Input::DOWN);
            if (m_event->key.code == sf::Keyboard::Left)
                inputs.push_back(Input::LEFT);
            if (m_event->key.code == sf::Keyboard::Right)
                inputs.push_back(Input::RIGHT);
            if (m_event->key.code == sf::Keyboard::Space)
                inputs.push_back(Input::SHOOT);
        }
    }
    return inputs;
}

bool GUI::GUI::isOpen()
{
    return m_window->isOpen();
}

GUI::GUI::~GUI()
{
    for (auto sprite : m_sprites)
        delete sprite.second;
    delete m_window;
    delete m_event;
}
