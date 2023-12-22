/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Core
*/

#include "Core.hpp"

// Constructors ---------------------------------------------------------------

// You can create start entities here
ECS::Core::Core(GUI::IGUI &gui): _gui(gui)
{
    Registry &registry = get_registry();

    entity e = registry.spawn_entity();
    registry.add_component(e, component::Position(0, 0));
    registry.add_component(e, component::Velocity(0, 0));
    registry.add_component(e, component::Drawable("../assets/images/player_idle.png"));
    registry.add_component(e, component::Controllable(10, 0.9));
    registry.add_component(e, component::HitBox(100, 100));
}

ECS::Core::~Core()
{
}

// Methods --------------------------------------------------------------------

GUI::IGUI &ECS::Core::get_gui()
{
    return _gui;
}

Registry &ECS::Core::get_registry()
{
    return _registry;
}
