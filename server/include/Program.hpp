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
        "USAGE: ./r-type_server [-h/--help] [-p/--port <port>]\n\n"
        "DESCRIPTION:\n"
        "\tport\tport of the server (1024 < port < 65535) - 4242 by default\n";

    enum class RunMode {
        HELP = 0,
        RUN = 1,
    };

    class Params {
    public:
        Params(const vector<string> args);
        ~Params() = default;

        RunMode runMode = RunMode::RUN;
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
