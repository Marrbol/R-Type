/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Registry
** The registry is responsible for storing all the components and entities, as
** a database would behave.
*/

#pragma once

#include <cstddef>
#include <functional>
#include <vector>
#include <any>
#include <typeindex>
#include <type_traits>
#include <string>
#include <unordered_map>

#include "SparseArray.hpp"
#include "Entity.hpp"

class Registry {
public:

    Registry();
    ~Registry();

    template<class Component>
    sparse_array<Component> &register_component();

    template<class Component>
    sparse_array<Component> &get_components();

    template<class Component>
    sparse_array<Component> const &get_components() const;

    entity spawn_entity();

    entity entity_from_index(std::size_t idx);

    void kill_entity(entity const &e);

    template<typename Component>
    typename sparse_array<Component>::reference_type add_component(entity const &to, Component &&c);

    template<typename Component, typename ... Params>
    typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&...p);

    template<typename Component>
    void remove_component(entity const &from);

private:

    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::unordered_map<std::type_index, std::function<void(Registry &, entity const &)>> _on_kill_callbacks;
    std::size_t _next_entity_idx = 0;
};

// IMPLEMENTATION (in header file because of templates)

template<typename Component>
sparse_array<Component> &Registry::register_component()
{
    _components_arrays[std::type_index(typeid(Component))] = sparse_array<Component>();
    _on_kill_callbacks[std::type_index(typeid(Component))] = [](Registry &r, entity const &e) {
        r.remove_component<Component>(e);
    };
    return get_components<Component>();
}

template<typename Component>
sparse_array<Component> &Registry::get_components()
{
    std::any &components = _components_arrays.at(std::type_index(typeid(Component)));
    return std::any_cast<sparse_array<Component> &>(components);
}

template<typename Component>
sparse_array<Component> const &Registry::get_components() const
{
    std::any const &components = _components_arrays.at(std::type_index(typeid(Component)));
    return std::any_cast<sparse_array<Component> const &>(components);
}

template<typename Component>
typename sparse_array<Component>::reference_type Registry::add_component(entity const &to, Component &&c)
{
    auto &components = get_components<Component>();
    return components.insert_at(to, std::forward<Component>(c));
}

template<typename Component, typename ...Params>
typename sparse_array<Component>::reference_type Registry::emplace_component(entity const &to, Params &&...p)
{
    auto &components = get_components<Component>();
    return components.emplace_at(to, std::forward<Params>(p)...);
}

template<typename Component>
void Registry::remove_component(entity const &from)
{
    auto &components = get_components<Component>();
    components.erase(from);
    auto &on_kill = _on_kill_callbacks.at(std::type_index(typeid(Component)));
    on_kill(*this, from);
}
