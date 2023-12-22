/*
** EPITECH PROJECT, 2023
** RType
** File description:
** SystemHandler
*/

#include "Physics/PhysicsModule.hpp"
#include "Render/RenderModule.hpp"
#include "Control/ControlModule.hpp"
#include "DestroyOutOfBounds/DestroyOutOfBoundsModule.hpp"

// Constructors ---------------------------------------------------------------

// Feel free to register your own systems here
ECS::SystemHandler::SystemHandler(ECS::Core &core): _core(core)
{
    load_system(&Control::run);
    load_system(&Physics::run);
    load_system(&Render::run);
    load_system(&DestroyOutOfBounds::run);
}

ECS::SystemHandler::~SystemHandler()
{
    for (auto handle : _handles) {
        LIB_CLOSE(handle);
    }
}

// Methods --------------------------------------------------------------------

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

/* Won't be used unless the libraries become shared instead of static

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
