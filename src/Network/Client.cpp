/*
** EPITECH PROJECT, 2023
** RType
** File description:
** NetworkClient
*/

#include "Network.hpp"

#include <thread>

Network::Client::Client(const std::string &ip, short port)
    : m_socket(m_io_context, udp::endpoint(udp::v4(), 0))
{
    udp::resolver resolver(m_io_context);
    udp::resolver::query query(udp::v4(), ip, std::to_string(port));
    m_sender_endpoint = *resolver.resolve(query);
}

void Network::Client::do_receive()
{
    m_socket.async_receive_from(
        buffer(m_data, max_length), m_sender_endpoint,
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                handle_received_data(length);
            }
            do_receive();
        }
    );
}

void Network::Client::handle_received_data(std::size_t length)
{
    std::cout.write(m_data, length);
    std::cout << std::endl;

    m_socket.async_send_to(
        buffer(m_data, length), m_sender_endpoint,
        [this](boost::system::error_code ec, std::size_t length) {
        }
    );

    for (int i = 0; i < max_length; ++i)
        m_data[i] = 0;

    std::cout << "Sent" << std::endl;
}

void Network::Client::run()
{
    do_receive();
    std::thread t([this]() {
        m_io_context.run();
    });
    t.join();
}

Network::Client::~Client()
{
}
