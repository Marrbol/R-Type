/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkServer
*/

#include "NetworkServer.hpp"

#include <thread>

Network::Session::~Session()
{
}

void Network::Session::start()
{
    doRead();
}

void Network::Session::doRead()
{
    auto self(shared_from_this());
    m_socket.async_read_some(
        boost::asio::buffer(m_data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                doWrite(length);
            }
        });
}

void Network::Session::doWrite(std::size_t length)
{
    auto self(shared_from_this());
    boost::asio::async_write(
        m_socket, boost::asio::buffer(m_data, length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                doRead();
            }
        });
}

Network::NetworkServer::NetworkServer(short port):
    m_acceptor(m_io_context, tcp::endpoint(tcp::v4(), port)), m_socket(m_io_context)
{
}

void Network::NetworkServer::doAccept()
{
    m_acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->start();
            }
            doAccept();
        }
    );
}

void Network::NetworkServer::run()
{
    doAccept();
    std::thread t([this]() {
        m_io_context.run();
    });
    t.join();
}

Network::NetworkServer::~NetworkServer()
{
}
