#pragma once

#include <memory>
#include <set>
#include <components/sprite.hpp>

class RenderSystem {
    public:
        static RenderSystem& get();

        void process();

        void registerObject(std::shared_ptr<SpriteComponent> object);
        void unregisterObject(std::shared_ptr<SpriteComponent> object);

    private:
        typedef std::multiset<std::shared_ptr<SpriteComponent>> SpriteSet;

        RenderSystem();
        RenderSystem(const RenderSystem&) = delete;
        void operator = (const RenderSystem&) = delete;

        SpriteSet _background;
        SpriteSet _terran_tiles;
        SpriteSet _objects;
        SpriteSet _gui;
};
