#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include "any.hpp"

class Component;

class GameEntity {
    public:
        typedef std::function<Any(void)> PropertyCallback;

        GameEntity()
            : _self(std::shared_ptr<GameEntity>(this))
        { }

        // c must be created on the heap
        void attachComponent(Component& c)
        {
            _components.insert(std::shared_ptr<Component>(&c));
        }
            
        std::shared_ptr<GameEntity> obtainPtr() const
        {
            return _self;
        }

        Any getProperty(const std::string& id)
        {
            assert(!_map.empty());
            auto found = _map.find(id);
            assert(found != _map.end());
            return found->second();
        }

    private:
        void provideProperty(const std::string& id, PropertyCallback callback)
        {
            auto result = _map.insert(std::make_pair(id, callback));
            assert(result.second);
            assert(_map.find("test") != _map.end());
        }

        std::unordered_map<std::string, PropertyCallback> _map;
        std::shared_ptr<GameEntity> _self;
        std::set<std::shared_ptr<Component>> _components;

        friend class Component;
};
