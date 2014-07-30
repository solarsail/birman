#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>

template<class T>
using StorageType = typename std::decay<T>::type;

struct Any
{
    bool is_null() const { return !_ptr; }

    template<typename ValueType> Any(ValueType&& value)
        : _ptr(std::static_pointer_cast<Base>(
                    std::make_shared<Derived<StorageType<ValueType>>>(std::forward<ValueType>(value))))
    { }

    template<class ValueType> bool is() const
    {
        typedef StorageType<ValueType> T;

        auto derived = std::dynamic_pointer_cast<Derived<T>> (_ptr);

        return derived;
    }

    template<class ValueType> StorageType<ValueType>& as()
    {
        typedef StorageType<ValueType> T;

        auto derived = std::dynamic_pointer_cast<Derived<T>> (_ptr);

        if (!derived) {
            throw std::bad_cast();
        }

        return derived->value;
    }

    template<class ValueType> operator ValueType()
    {
        return as<ValueType>();
    }

    Any()
        : _ptr(nullptr)
    { }

    Any(const Any& that)
        : _ptr(that._ptr)
    { }

    Any(Any&& that)
        : _ptr(that._ptr)
    { }

    Any& operator=(const Any& a)
    {
        if (_ptr == a._ptr)
            return *this;

        _ptr = a._ptr;

        return *this;
    }

    Any& operator=(Any&& a)
    {
        *this = a;

        return *this;
    }

private:
    struct Base
    {
        virtual ~Base() {}
    };

    template<typename StorageType>
        struct Derived : Base
    {
        template<typename ValueType>
            Derived(ValueType&& value) : value(std::forward<ValueType>(value)) { }

        StorageType value;
    };

    std::shared_ptr<Base> _ptr;
};
