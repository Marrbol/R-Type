/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkServer
*/

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <unordered_set>
#include <unordered_map>

using namespace boost::asio;
using ip::udp;

namespace Network {

    enum Event : int {
        CONNECTED,
        DISCONNECTED,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        SHOOT,
        COUNT
    };

    class INetwork {
    public:
        virtual ~INetwork() = default;
        virtual void run() = 0;
    };

    class Server : public INetwork {
    public:
        template <typename... Args>
        using Callback = std::function<void(udp::endpoint &, Args...)>;

        // Constructors
        Server(short port);
        ~Server();

        // Methods
        void run(); // Launches the server

        template <typename... Args>
        void send_to(udp::endpoint &endpoint, Event event, Args... args);

        void send_to(udp::endpoint &endpoint, Event event);

        template <typename... Args>
        void send_to_all(Event event, Args... args);

        void send_to_all(Event event);

        template <typename... Args>
        void connect(Event type, Callback<Args...> callback); // connects a callback to an event

    private:

        void startReceiving();

        void handleReceivedData(std::size_t length);

        template <typename... Args>
        void trigger(Event eventType, Args&&... args);

        std::unordered_map<Event, std::vector<Callback<>>> _callbacks;
        io_context _io_context;
        udp::endpoint _sender_endpoint;
        udp::socket _socket;
        std::unordered_set<udp::endpoint *> _clients;
        enum { max_length = 1024 };
        char _data[max_length];
    };

    class Client : public INetwork {
    public:
        template <typename... Args>
        using Callback = std::function<void(Args...)>;

        // Constructors
        Client(const std::string &ip, short port);
        ~Client();

        // Methods
        void run(); // Launches the client

        template <typename... Args>
        void send(Event type, Args... args);

        void send(Event type);

        template <typename... Args>
        void connect(Event type, Callback<Args...> callback); // connects a callback to an event

    private:

        void startReceiving();

        void handleReceivedData(std::size_t length);

        template <typename... Args>
        void trigger(Event eventType, Args&&... args);

        std::unordered_map<Event, std::vector<Callback<>>> _callbacks;
        io_context _io_context;
        udp::endpoint _sender_endpoint;
        udp::socket _socket;
        enum { max_length = 1024 };
        char _data[max_length];
    };

}
