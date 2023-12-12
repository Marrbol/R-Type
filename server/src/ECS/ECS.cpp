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
    m_registry = new Registry; // Holds all the entities and components
    m_gui = new GUI::GUI; // Receives elements to draw and gives inputs
    m_systemHandler = new SystemHandler(*m_registry, *m_gui); // Runs the systems
    m_network = new Network::NetworkServer(params.port); // Manages the network
}

ECS::ECS::~ECS()
{
    delete m_registry;
    delete m_gui;
    delete m_systemHandler;
    delete m_network;
}

// Main loop ------------------------------------------------------------------

void ECS::ECS::run()
{
    std::thread network_thread(&Network::NetworkServer::run, m_network);
    std::thread system_thread(&SystemHandler::run, m_systemHandler);

    system_thread.join();
    network_thread.join();
}
