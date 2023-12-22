/*
** EPITECH PROJECT, 2023
** RType - ECS
** File description:
** Program
** Manage everything related to the program separately from the ECS.
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
        "USAGE: ./r-type [-h/--help]\n"
        "\n"
        "DESCRIPTION:\n"
        "\t-h/--help\tdisplay this help and exit\n";

    enum class RunMode {
        HELP = 0,
        RUN = 1,
        NONE = 2
    };

    class Params {
    public:
        Params(const vector<string> args);
        ~Params() = default;

        RunMode runMode = RunMode::NONE;
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
