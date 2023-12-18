/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkClient
*/

#include "Network.hpp"

#include <thread>

// Constructors ---------------------------------------------------------------

Network::Client::Client(const std::string &ip, short port)
    : _socket(_io_context)
{
    udp::resolver resolver(_io_context);
    udp::resolver::query query(udp::v4(), ip, std::to_string(port));
    _sender_endpoint = *resolver.resolve(query);
    _socket.open(_sender_endpoint.protocol());
}

Network::Client::~Client()
{
}

// Public methods -------------------------------------------------------------

template <typename... Args>
void Network::Client::send(Event type, Args... args)
{
    _socket.send_to(buffer(&type, sizeof(type)), _sender_endpoint);
    for (const auto& arg : {args...}) {
        std::stringstream ss;
        ss << arg;
        std::string data = ss.str();
        _socket.send_to(buffer(data.c_str(), data.size()), _sender_endpoint);
    }
}

void Network::Client::send(Event type)
{
    _socket.send_to(buffer(&type, sizeof(type)), _sender_endpoint);
}

template <typename... Args>
void Network::Client::connect(Event type, Callback<Args...> callback)
{
    _callbacks[type].push_back(callback);
}

void Network::Client::run()
{
    std::cout << "Client running" << std::endl;
    startReceiving();
    std::thread t([this]() {
        _io_context.run();
    });
    t.join();
}

// Private methods ------------------------------------------------------------

void Network::Client::startReceiving()
{
    _socket.async_receive_from(
        buffer(_data, max_length), _sender_endpoint,
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec && length > 0) {
                handleReceivedData(length);
            }
            startReceiving();
        });
}

template <typename... Args>
void Network::Client::trigger(Event eventType, Args&&... args)
{
    if (_callbacks.find(eventType) != _callbacks.end()) {
        for (const auto& callback : _callbacks[eventType]) {
            callback(std::forward<Args>(args)...);
        }
    }
}

void Network::Client::handleReceivedData(std::size_t length)
{
    std::istringstream iss(std::string(_data, length));
    Event eventType;
    iss.read(reinterpret_cast<char *>(&eventType), sizeof(eventType));

    // Deserialize the arguments and invoke the callbacks
    if (_callbacks.find(eventType) != _callbacks.end()) {
        switch (eventType) {
            case Event::MOVE_UP:
            case Event::MOVE_DOWN:
            case Event::MOVE_LEFT:
            case Event::MOVE_RIGHT:
            case Event::SHOOT:
            case Event::CONNECTED:
            case Event::DISCONNECTED:
            default:
                break;
        }
    }
}
