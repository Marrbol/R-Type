/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-oceane.krull
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum state {
    Stopped,
    Paused,
    Playing,
    Undefined
};

class Music {
    public:
        Music();
        ~Music();
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

    protected:
    private:
        sf::Music _music;
};

#endif /* !Music_HPP_ */
