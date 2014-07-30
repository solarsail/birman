#pragma once

#include <functional>
#include <memory>
#include "entity.hpp"

class Component {
    public:
        Component(GameEntity& entity)
            : _entity(entity.obtainPtr())
        {
            _entity->attachComponent(*this);
        }
            
        void provideProperty(const std::string& id, GameEntity::PropertyCallback callback)
        {
            _entity->provideProperty(id, callback);
        }

        virtual ~Component() {};

    private:
        std::shared_ptr<GameEntity> _entity;
};
