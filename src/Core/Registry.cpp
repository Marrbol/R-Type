/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Registry
*/

#include <cstddef>

#include "Core/Registry.hpp"
#include "Core/Component.hpp"

#include "GUI.hpp"

// Most of the code was moved to the header file, because of the templates

Registry::Registry()
{
}

Registry::~Registry()
{
}

entity Registry::spawn_entity()
{
    entity e(_next_entity_idx++);
    return e;
}

entity Registry::entity_from_index(std::size_t idx)
{
    entity e(idx);
    return e;
}

void Registry::kill_entity(entity const &e)
{
    for (auto &components : _components_arrays) {
        auto &on_kill = _on_kill_callbacks.at(components.first);
        on_kill(*this, e);
    }
}
