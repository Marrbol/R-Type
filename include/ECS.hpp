/*
** EPITECH PROJECT, 2023
** RType
** File description:
** ECS
*/

#pragma once

#include <cstddef>

#include "Program.hpp"

#include "ECS/SparseArray.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Registry.hpp"
#include "ECS/Component.hpp"
#include "ECS/SystemHandler.hpp"

#include "Network.hpp"
#include "GUI.hpp"

namespace ECS {

    class ECS {
    public:
        ECS(const Program::Params &params);
        ~ECS();
        void run();
    private:

        Registry *m_registry = nullptr;
        GUI::GUI *m_gui = nullptr;
        SystemHandler *m_systemHandler = nullptr;
        Network::INetwork *m_network = nullptr;
    };

    class RuntimeException : public std::exception {
    public:
        RuntimeException(const std::string &message) : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }
    private:
        std::string _message;
    };

}
