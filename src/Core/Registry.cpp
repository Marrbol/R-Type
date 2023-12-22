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

// Constructors ---------------------------------------------------------------

// Feel free to register your own components here
Registry::Registry()
{
    register_component<component::Position>();
    register_component<component::Velocity>();
    register_component<component::Drawable>();
    register_component<component::Controllable>();
    register_component<component::HitBox>();
    register_component<component::BoundsLimit>();
    register_component<component::Respawnable>();
}

Registry::~Registry()
{
}

// Methods --------------------------------------------------------------------

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
