/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GUI
** This is the GUI class, it is used to display the game. Its only goal is to
** behave as a render window and encapsulate anything SFML related. Feel free
** to implement your own GUI class, relying on whatever library you want.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace GUI {

    /*
    ** An Appearance enum was considered to avoid spreading sf elements into
    ** the register so IGUI would completely encapsulate anything
    ** library-related, and IGUI::draw would take this enum as parameter.
    ** Just keeping it here for the record.
    */

    enum class Input : int {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        COUNT
    };

    enum state {
        Stopped,
        Paused,
        Playing,
        Undefined
    };

    class IGUI {
    public:
        virtual ~IGUI() = default;
        virtual void clear() = 0;
        virtual void draw(sf::Sprite &sprite, float x, float y, float width, float height) = 0;
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
        void draw(sf::Sprite &sprite, float x, float y, float width, float height);
        void display();
        std::vector<Input> getInputs();
        bool isOpen();
        size_t get_width() const;
        size_t get_height() const;
        ~SfmlGUI();
        bool openFromFile(const std::string &filename);
        bool getLoop();
        void setLoop(bool loop);
        float getAttenuation();
        void setAttenuation(float attenuation);
        float getPitch();
        void setPitch(float pitch);
        float getVolume();
        void setVolume(float volume);
        state getStatus();
        void pause();
        void play();

    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Music _music;
    };

}
