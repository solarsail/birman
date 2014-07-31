#pragma once

#include <functional>
#include <memory>
#include "entity.hpp"

class ComponentFactory;

class Component {
    public:
		Component();
        virtual ~Component();

    protected:
        virtual void registerProperty(std::shared_ptr<GameEntity> entity);

    private:
        

    private:
        std::shared_ptr<GameEntity> _entity;

        friend class ComponentFactory;
        friend class GameEntity;
};
