#include "systems/render.hpp"

RenderSystem& RenderSystem::get()
{
    static RenderSystem instance;
    return instance;
}

RenderSystem::RenderSystem() { }

void RenderSystem::process()
{
}

void RenderSystem::registerObject(std::shared_ptr<SpriteComponent> object)
{
    _objects.insert(object);
}

void RenderSystem::unregisterObject(std::shared_ptr<SpriteComponent> object)
{
    _objects.erase(object);
}
