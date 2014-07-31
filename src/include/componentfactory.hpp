#pragma once

#include <memory>
#include <type_traits>

class Component;

class ComponentFactory {
    public:
        template <class T>
        std::shared_ptr<T> create()
        {
            static_assert(std::is_base_of<Component, T>::value, "Attempt to instantiate non Component derived classes");
            return std::make_shared<T>();
        }
};
