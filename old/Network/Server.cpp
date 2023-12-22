/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkServer
*/

#include "Network.hpp"

#include <thread>

// Constructors ---------------------------------------------------------------

Network::Server::Server(short port):
    _socket(_io_context, udp::endpoint(udp::v4(), port))
{
}

Network::Server::~Server()
{
}

// Public methods -------------------------------------------------------------

template <typename... Args>
void Network::Server::send_to(udp::endpoint &endpoint, Event type, Args... args)
{
    _socket.send_to(buffer(&type, sizeof(type)), endpoint);
    for (const auto& arg : {args...}) {
        std::stringstream ss;
        ss << arg;
        std::string data = ss.str();
        _socket.send_to(buffer(data.c_str(), data.size()), endpoint);
    }
}

void Network::Server::send_to(udp::endpoint &endpoint, Event type)
{
    _socket.send_to(buffer(&type, sizeof(type)), endpoint);
}

template <typename... Args>
void Network::Server::send_to_all(Event type, Args... args)
{
    for (auto &client : _clients) {
        send_to(*client, type, args...);
    }
}

void Network::Server::send_to_all(Event type)
{
    for (auto &client : _clients) {
        send_to(*client, type);
    }
}

template <typename... Args>
void Network::Server::connect(Event type, Callback<Args...> callback)
{
    _callbacks[type].push_back(callback);
}

void Network::Server::run()
{
    std::cout << "Server running" << std::endl;
    startReceiving();
    std::thread t([this]() {
        _io_context.run();
    });
    t.join();
}

// Private methods ------------------------------------------------------------

void Network::Server::startReceiving()
{
    _socket.async_receive_from(
        boost::asio::buffer(_data), _sender_endpoint,
        [this](const boost::system::error_code& error, std::size_t bytesTransferred) {
            if (!error) {
                handleReceivedData(bytesTransferred);
                startReceiving();  // Continue listening for more data
            } else {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            }
        });
}

template <typename... Args>
void Network::Server::trigger(Event eventType, Args&&... args)
{
    if (_callbacks.find(eventType) != _callbacks.end()) {
        for (const auto& callback : _callbacks[eventType]) {
            callback(_sender_endpoint, std::forward<Args>(args)...);
        }
    }
}

void Network::Server::handleReceivedData(std::size_t length)
{
    std::istringstream iss(std::string(_data, length));

    // Identify the event type (assuming EventType is the first field)
    Event eventType;
    iss.read(reinterpret_cast<char*>(&eventType), sizeof(Event));

    // Deserialize the arguments and invoke the callbacks
    if (_callbacks.find(eventType) != _callbacks.end()) {
        switch (eventType) {
            case Event::MOVE_UP:
            case Event::MOVE_DOWN:
            case Event::MOVE_LEFT:
            case Event::MOVE_RIGHT:
            case Event::SHOOT:
            case Event::CONNECTED:
                std::cout << "Received event " << eventType << std::endl;
                break;
            case Event::DISCONNECTED:
            default:
                break;
        }
    }
}
