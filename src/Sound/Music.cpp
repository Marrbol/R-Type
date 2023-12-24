/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-oceane.krull
** File description:
** Sound
*/

#include "Sound.hpp"

Music::Music()
{
}

Music::~Music()
{
}

bool Music::openFromFile(const std::string &filename)
{
    _music.openFromFile(filename);
}

bool Music::getLoop()
{
    return _music.getLoop();
}

void Music::setLoop(bool loop)
{
    _music.setLoop(loop);
}

bool Music::openFromFile(const std::string &filename)
{
    return _music.openFromFile(filename);
}

float Music::getAttenuation()
{
    return _music.getAttenuation();
}

void Music::setAttenuation(float attenuation)
{
    _music.setAttenuation(attenuation);
}

float Music::getPitch()
{
    return _music.getPitch();
}

void Music::setPitch(float pitch)
{
    _music.setPitch(pitch);
}

float Music::getVolume()
{
    return _music.getVolume();
}

void Music::setVolume(float volume)
{
    _music.setVolume(volume);
}

state Music::getStatus()
{
    sf::Sound::Status res = _music.getStatus();

    switch (res) {
    case sf::Sound::Status::Stopped:
        return state::Stopped;
        break;
    case sf::Sound::Status::Paused:
        return state::Paused;
        break;
    case sf::Sound::Status::Playing:
        return state::Playing;
        break;
    default:
        return state::Undefined;
        break;
    }
}

void Music::pause()
{
    _music.pause();
}

void Music::play()
{
    _music.play();
}

