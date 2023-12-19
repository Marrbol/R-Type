/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GUI
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <unordered_map>

namespace GUI {

    enum class Input : int {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SHOOT,
        COUNT
    };

    class IGUI {
    public:
        virtual ~IGUI() = default;
        virtual void clear() = 0;
        virtual void draw(sf::Sprite &sprite) = 0;
        virtual void display() = 0;
        virtual std::vector<Input> getInputs() = 0;
        virtual bool isOpen() = 0;
        virtual size_t get_width() const = 0;
        virtual size_t get_height() const = 0;
    };

    class SfmlGUI : public IGUI {
    public:
        SfmlGUI();
        void clear();
        void draw(sf::Sprite &sprite);
        void display();
        std::vector<Input> getInputs();
        bool isOpen();
        size_t get_width() const;
        size_t get_height() const;
        ~SfmlGUI();
    private:
        sf::RenderWindow _window;
        sf::Event _event;
    };

}
