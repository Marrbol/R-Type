/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GUI
*/

#include "GUI.hpp"

GUI::SfmlGUI::SfmlGUI():
    _window({800, 600}, "R-Type")
{
    _window.setFramerateLimit(60);
    _window.setKeyRepeatEnabled(true);
}

GUI::SfmlGUI::~SfmlGUI()
{
}

void GUI::SfmlGUI::draw(sf::Sprite &sprite, size_t x, size_t y)
{
    sprite.setPosition(x, y);
    _window.draw(sprite);
}

void GUI::SfmlGUI::clear()
{
    _window.clear();
}

void GUI::SfmlGUI::display()
{
    _window.display();
}

size_t GUI::SfmlGUI::get_width() const
{
    return _window.getSize().x;
}

size_t GUI::SfmlGUI::get_height() const
{
    return _window.getSize().y;
}

std::vector<GUI::Input> GUI::SfmlGUI::getInputs()
{
    std::vector<Input> inputs;

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (!_window.hasFocus())
            continue;
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Up:
                    inputs.push_back(Input::UP);
                    break;
                case sf::Keyboard::Down:
                    inputs.push_back(Input::DOWN);
                    break;
                case sf::Keyboard::Left:
                    inputs.push_back(Input::LEFT);
                    break;
                case sf::Keyboard::Right:
                    inputs.push_back(Input::RIGHT);
                    break;
                case sf::Keyboard::Space:
                    inputs.push_back(Input::SPACE);
                    break;
                default:
                    break;
            }
        }
    }
    return inputs;
}

bool GUI::SfmlGUI::isOpen()
{
    return _window.isOpen();
}
