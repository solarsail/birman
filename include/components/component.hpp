#pragma once

#include <memory>

class Component {
    public:
        Component(GameEntity& entity);
        virtual ~Component();

    private:
        std::shared_ptr<GameEntity> _entity;
};
