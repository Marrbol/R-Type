/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#include "Core.hpp"
#include <stdio.h>
#include <iostream>
#include <functional>
#include <memory>
#include <filesystem>

// Temporary forward declarations

void control_system(ECS::Core &c);
void draw_system(ECS::Core &c);
void physics_system(ECS::Core &c);

ECS::SystemHandler::SystemHandler(ECS::Core &core): _core(core)
{
    // Will be used when loading from shared libraries

    // load_system("PhysicsModule");
    // load_system("RenderModule");
    // load_system("ControlModule");

    // In the meantime :

    load_system(control_system);
    load_system(physics_system);
    load_system(draw_system);
}

ECS::SystemHandler::~SystemHandler()
{
    for (auto handle : _handles) {
        LIB_CLOSE(handle);
    }
}

void ECS::SystemHandler::run()
{
    for (auto system : _systems) {
        system(_core);
    }
}

void ECS::SystemHandler::load_system(ECS::SystemHandler::System system)
{
    _systems.push_back(system);
}

/*
void ECS::SystemHandler::load_system(const std::string &path)
{
    std::string realPath = std::string("lib/lib") + path + LIB_EXT;
    LIB_HANDLE handle = LIB_LOAD(realPath.c_str());
    if (!handle)
        throw RuntimeException(std::string("Cannot load library: ") + LIB_ERROR());
    void(*sym)(ECS::Core &) = reinterpret_cast<void(*)(ECS::Core &)>(LIB_GETSYM(handle, "run"));
    if (!sym)
        throw RuntimeException(std::string("Cannot find symbol: ") + LIB_ERROR());
    System system = std::bind(sym, std::ref(_core));
    _handles.push_back(handle);
    _systems.push_back(system);
}
*/

// Systems (temporary location) -----------------------------------------------

void control_system(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &velocities = registry.get_components<component::Velocity>();
    auto &controllables = registry.get_components<component::Controllable>();

    for (size_t i = 0; i < velocities.size() && i < controllables.size(); ++i) {
        auto &vel = velocities[i];
        auto &cont = controllables[i];

        if (vel && cont) {
            std::vector<GUI::Input> inputs = gui.getInputs();
            for (auto input : inputs) {
                if (input == GUI::Input::UP)
                    vel.value().y -= cont.value().speed;
                if (input == GUI::Input::DOWN)
                    vel.value().y += cont.value().speed;
                if (input == GUI::Input::LEFT)
                    vel.value().x -= cont.value().speed;
                if (input == GUI::Input::RIGHT)
                    vel.value().x += cont.value().speed;
            }
        }
    }
}

void draw_system(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &positions = registry.get_components<component::Position>();
    auto &drawables = registry.get_components<component::Drawable>();

    gui.clear();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
        auto &pos = positions[i];
        auto &draw = drawables[i];

        if (pos && draw) {
            gui.draw(draw->sprite);
        }
    }

    gui.display();
}

void physics_system(ECS::Core &c)
{
    auto &registry = c.get_registry();
    auto &gui = c.get_gui();

    auto &positions = registry.get_components<component::Position>();
    auto &velocities = registry.get_components<component::Velocity>();
    auto &controllables = registry.get_components<component::Controllable>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto &pos = positions[i];
        auto &vel = velocities[i];
        auto &cont = controllables[i];

        if (pos && vel) {
            pos->x += vel->x;
            pos->y += vel->y;
            if (cont) {
                if (pos->x < 0)
                    pos->x = 0;
                if (pos->y < 0)
                    pos->y = 0;
                if (pos->x > gui.get_width())
                    pos->x = gui.get_width();
                if (pos->y > gui.get_height())
                    pos->y = gui.get_height();
                vel->x *= cont->slow;
                vel->y *= cont->slow;
            }
        }
    }
}
