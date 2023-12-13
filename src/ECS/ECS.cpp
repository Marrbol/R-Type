/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ECS
*/

#include "ECS.hpp"

#include <thread>

// Constructors ---------------------------------------------------------------

ECS::ECS::ECS(const Program::Params &params)
{
    m_registry = new Registry;

    if (params.runMode == Program::RunMode::CLIENT) { // Client mode
        m_network = new Network::Client(params.ip, params.port);
        m_gui = new GUI::GUI;
        m_systemHandler = new SystemHandler(*m_registry, *m_gui);

    } else if (params.runMode == Program::RunMode::SERVER) { // Server mode
        m_network = new Network::Server(params.port);
        m_systemHandler = new SystemHandler(*m_registry);
    }
}

ECS::ECS::~ECS()
{
    delete m_registry;
    if (m_gui)
        delete m_gui;
    delete m_systemHandler;
    delete m_network;
}

// Main loop ------------------------------------------------------------------

void ECS::ECS::run()
{
    std::thread network_thread(&Network::INetwork::run, m_network);
    std::thread system_thread(&SystemHandler::run, m_systemHandler);

    system_thread.join();
    network_thread.join();
}
