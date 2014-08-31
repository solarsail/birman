#pragma once

#include <memory>
#include <set>
#include "components/sprite.hpp"
#include "context.hpp"
#include "systems/map.hpp"

class RenderSystem {
    public:
        typedef std::shared_ptr<GameEntity> EntityPtr;
        typedef std::multiset<EntityPtr> EntitySet;

        static RenderSystem& get();

        void process(GameContext& ctx);
        void init(GameContext& ctx, EntityPtr player);
        void setMap(Map& map);

        void registerObject(EntityPtr entity);
        void unregisterObject(EntityPtr entity);

    private:
        RenderSystem();
        ~RenderSystem();
        RenderSystem(const RenderSystem&);
        void operator = (const RenderSystem&);

        void reloadMapSlice(sf::Vector2f origin);

        Map* _terrainPtr;
        EntitySet _objects;
        EntityPtr _player;
        EntitySet _weather;
        EntitySet _gui;

        MapSlice* _mapSlicePtr;
        sf::FloatRect _reloadBound;
        sf::Vector2f _lastCenter;
};
