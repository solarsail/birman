#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "component/component.hpp"

class PropertyBase {};

template <class Derived>
class Property : public PropertyBase {
    public:
        Derived::PropertyType getValue() const
        {
            return static_cast<Derived*>(this)->value();
        }
};

class GameEntity {
    public:
        void attachComponent(Component& c);
        std::shared_ptr<GameEntity> obtainPtr() const;

    private:
        template <typename T>
        void provideProperty(const std::string& id, std::function<std::unique_ptr<PropertyBase>(void)> callback);

        template <typename T>
        T getProperty(const std::string& id);

        std::unordered_map<std::string, 
        friend class Component;
};
