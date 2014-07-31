#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include "any.hpp"

class Component;
class GameEntityFactory;

class GameEntity : public std::enable_shared_from_this<GameEntity> {
    public:
        typedef std::function<Any(void)> PropertyCallback;

        void attachComponent(std::shared_ptr<Component> c);
            
        void provideProperty(const std::string& id, PropertyCallback callback);
        Any getProperty(const std::string& id);

    private:
        GameEntity();

        std::unordered_map<std::string, PropertyCallback> _map;
        std::set<std::shared_ptr<Component>> _components;

        friend class Component;
        friend class GameEntityFactory;
};
