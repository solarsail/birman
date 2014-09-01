#pragma once

#include <memory>
#include <set>
#include "components/sprite.hpp"
#include "context.hpp"
#include "systems/map.hpp"

class RenderSystem {
    public:
        typedef std::multiset<GameEntityPtr> EntitySet;

        static RenderSystem& get();

        void process(GameContext& ctx);
        void init(GameContext& ctx, GameEntityPtr player);
        void setMap(Map& map);

        void registerObject(GameEntityPtr entity);
        void unregisterObject(GameEntityPtr entity);

    private:
        RenderSystem();
        ~RenderSystem();
        RenderSystem(const RenderSystem&);
        void operator = (const RenderSystem&);

        void reloadMapSlice(sf::Vector2f origin);

        Map* _terrainPtr;
        EntitySet _objects;
        GameEntityPtr _player;
        EntitySet _weather;
        EntitySet _gui;

        MapSlice* _mapSlicePtr;
        sf::FloatRect _reloadBound;
        sf::Vector2f _lastCenter;
};
