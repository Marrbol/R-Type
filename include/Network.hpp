/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkServer
*/

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using ip::udp;

namespace Network {

    class INetwork {
    public:
        virtual ~INetwork() = default;
        virtual void run() = 0;
    };

    class Server : public INetwork {
    public:
        Server(short port);
        ~Server();
        void run();
    private:
        void do_receive();
        void handle_received_data(std::size_t length);
        io_context m_io_context;
        udp::endpoint m_sender_endpoint;
        udp::socket m_socket;
        enum { max_length = 1024 };
        char m_data[max_length];
    };

    class Client : public INetwork {
    public:
        Client(short port);
        ~Client();
        void run();
    private:
        void do_receive();
        void handle_received_data(std::size_t length);
        io_context m_io_context;
        udp::endpoint m_sender_endpoint;
        udp::socket m_socket;
        enum { max_length = 1024 };
        char m_data[max_length];
    };

}
