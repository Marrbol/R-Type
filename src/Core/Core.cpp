/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Core
*/

#include "Core.hpp"

// Constructors ---------------------------------------------------------------

ECS::Core::Core(GUI::IGUI &gui): _gui(gui)
{
    auto &registry = get_registry();

    registry.register_component<component::Position>();
    registry.register_component<component::Velocity>();
    registry.register_component<component::Drawable>();
    registry.register_component<component::Controllable>();
    registry.register_component<component::HitBox>();

    entity e = registry.spawn_entity();
    registry.add_component(e, component::Position{0, 0});
    registry.add_component(e, component::Velocity{0, 0});
    sf::Texture texture;
    texture.loadFromFile("../assets/images/player_idle.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    registry.add_component(e, component::Drawable{sprite, texture, 0});
    registry.add_component(e, component::Controllable{10, 0.9});
    registry.add_component(e, component::HitBox{100, 100});
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
