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

#include "GUI/Sprite.hpp"

namespace GUI {

    enum class Input {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SHOOT,
        NONE
    };

    enum class Appearance {
        PLAYER_IDLE,
        PLAYER_SHOOT,
        ENEMY_IDLE,
        ENEMY_SHOOT,
        BULLET,
        NONE
    };

    struct SpriteData;
    class Sprite;

    class IGUI {
    public:
        virtual ~IGUI() = default;
        virtual void clear() = 0;
        virtual void draw(float x, float y, Appearance appearance) = 0;
        virtual void display() = 0;
        virtual std::vector<Input> getInputs() = 0;
        virtual bool isOpen() = 0;
    };

    class GUI : public IGUI {
    public:
        GUI();
        void clear();
        void draw(float x, float y, Appearance appearance);
        void display();
        std::vector<Input> getInputs();
        bool isOpen();
        ~GUI();
    private:
        void loadSprites();

        sf::RenderWindow *m_window;
        sf::Event *m_event;

        std::unordered_map<Appearance, Sprite *> m_sprites;

        std::unordered_map<Appearance, SpriteData> m_sprites_data = {
            {Appearance::PLAYER_IDLE, {"../assets/images/player_idle.png", 100, 100, 1}},
            {Appearance::PLAYER_SHOOT, {"../assets/images/player_shoot.png", 100, 100, 1}},
            {Appearance::ENEMY_IDLE, {"../assets/images/enemy_idle.png", 100, 100, 1}},
            {Appearance::ENEMY_SHOOT, {"../assets/images/enemy_shoot.png", 100, 100, 1}},
            {Appearance::BULLET, {"../assets/images/bullet.png", 100, 100, 1}}
        };

        std::vector<Appearance> m_appearances = {
            Appearance::PLAYER_IDLE,
            Appearance::PLAYER_SHOOT,
            Appearance::ENEMY_IDLE,
            Appearance::ENEMY_SHOOT,
            Appearance::BULLET
        };
    };

    class Audio {
    public:
        Audio();
        ~Audio();
    };

}
