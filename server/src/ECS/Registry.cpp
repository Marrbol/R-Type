/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Registry
*/

#include <cstddef>

#include "ECS/Registry.hpp"
#include "ECS/Component.hpp"

// Most of the code was moved to the header file, because of the templates

Registry::Registry()
{
    register_component<component::Position>();
    register_component<component::Velocity>();
    register_component<component::Drawable>();
    register_component<component::Controllable>();

    entity e = spawn_entity();
    add_component(e, component::Position{400, 300});
    add_component(e, component::Velocity{0, 0});
    add_component(e, component::Drawable{GUI::Appearance::PLAYER_IDLE});
    add_component(e, component::Controllable{10, 0.9});
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
