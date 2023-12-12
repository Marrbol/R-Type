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
using ip::tcp;

namespace Network {

    class NetworkServer {
    public:
        NetworkServer(short port);
        ~NetworkServer();
        void run();
    private:
        void doAccept();
        io_context m_io_context;
        tcp::acceptor m_acceptor;
        tcp::socket m_socket;
    };

    class Session : public std::enable_shared_from_this<Session> {
    public:
        explicit Session(tcp::socket socket): m_socket(std::move(socket)) {}
        ~Session();
        void start();
    private:
        void doRead();
        void doWrite(std::size_t length);
        tcp::socket m_socket;
        enum { max_length = 1024 };
        char m_data[max_length];
    };

}
