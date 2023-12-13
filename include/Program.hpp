/*
** EPITECH PROJECT, 2023
** RType - ECS
** File description:
** Program namespace - manage everything related to the program separately from
** the ECS.
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace Program {

    inline const int exitSuccess = 0;
    inline const int exitError = 84;
    inline const char *help =
        "USAGE: ./r-type_server [-h/--help | -c/--client | -s/--server] [-p/--port <port>]\n\n"
        "DESCRIPTION:\n"
        "\t-h/--help\tdisplay this help and exit\n"
        "\t-c/--client\trun as a client\n"
        "\t-s/--server\trun as a server\n"
        "\tport\tport to connect with (1024 < port < 65535) - 4242 by default\n";

    enum class RunMode {
        HELP = 0,
        SERVER = 1,
        CLIENT = 2,
        NONE = 3
    };

    class Params {
    public:
        Params(const vector<string> args);
        ~Params() = default;

        RunMode runMode = RunMode::NONE;
        short port = 4242;
    };

    class InvalidParamsException : public exception {
    public:
        InvalidParamsException(const string &message) : _message(message) {}
        ~InvalidParamsException() = default;

        const char *what() const noexcept override { return _message.c_str(); }

    private:
        string _message;
    };
}
