#pragma once

#include <memory>

class GameEntity;

class GameEntityFactory {
    public:
        std::shared_ptr<GameEntity> newEntity();
        // TODO: 提供若干预定义实体的构造？
};

