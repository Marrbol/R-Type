/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#include "ECS/SystemHandler.hpp"
#include "GUI.hpp"

// Constructors ---------------------------------------------------------------

ClientSystemHandler::ClientSystemHandler(Core::Core &core, Network::Client &client, GUI::IGUI &gui):
    _core(core), _client(client), _gui(gui)
{
    gui.connect(GUI::Input::DOWN, [this, &client](){
        client.send(Network::Event::MOVE_DOWN);
    });
    gui.connect(GUI::Input::LEFT, [this, &client](){
        client.send(Network::Event::MOVE_LEFT);
    });
    gui.connect(GUI::Input::RIGHT, [this, &client](){
        client.send(Network::Event::MOVE_RIGHT);
    });
    gui.connect(GUI::Input::SHOOT, [this, &client](){
        client.send(Network::Event::SHOOT);
    });
    client.connect(Network::Event::CONNECTED, [](){
        std::cout << "SERVER" << std::endl;
    });

    client.send(Network::Event::CONNECTED);
}

ClientSystemHandler::~ClientSystemHandler()
{
    _client.send(Network::Event::DISCONNECTED);
}

ServerSystemHandler::ServerSystemHandler(Core::Core &core, Network::Server &server): // Constructor used for server
    _core(core), _server(server)
{
    server.connect(Network::Event::CONNECTED, [](udp::endpoint &endpoint){
        std::cout << "Client connected" << std::endl;
    });
}
