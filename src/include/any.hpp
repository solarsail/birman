#pragma once

#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>

//////////////////////////////////////////////////////////////////////
/// \brief 可以保存任意类型数据的模板类。
///        保存数据后其类型暂时不可见，外界必须了解其正确类型才能
///        取出数据。
///
//////////////////////////////////////////////////////////////////////
struct Any {

        //////////////////////////////////////////////////////////////////
        /// \brief 判断是否已保存数据。
        ///
        /// \return 无数据则返回 true
        ///
        //////////////////////////////////////////////////////////////////
        bool is_null() const { return !_ptr; }

        //////////////////////////////////////////////////////////////////
        /// \brief 构造函数。
        ///
        /// 1. 使用 std::decay 将 ValueType 的修饰符（&、const等）抹去，得到原始类型，设为 T。
        /// 2. 构造 Derived<T> 类型变量，将实际值 value 保存在变量中。
        /// 3. 构造指向该变量的智能指针（使用 std::make_shared）
        /// 4. 将指针转换成指向 Base 类型并保存在 _ptr 中。
        /// std::forward 用于保留参数的修饰符。
        ///
        /// \see is
        /// \see as
        ///
        //////////////////////////////////////////////////////////////////
        template<typename ValueType> Any(ValueType&& value)
            : _ptr(std::static_pointer_cast<Base>(
                        std::make_shared<Derived<typename std::decay<ValueType>::type>>(std::forward<ValueType>(value))))
        { }

        //////////////////////////////////////////////////////////////////
        /// \brief 判断保存的值是否为 ValueType 类型。
        ///
        /// 1. 使用 std::decay 将 ValueType 的修饰符（&、const等）抹去，得到原始类型，设为 T。
        /// 2. 尝试将 _ptr 转换为 Derived<T> 类型指针 derived。
        /// 3. 如果成功，则 derived 非空，转换为 bool 类型的 true，否则转换为 false。
        ///
        /// \return 如果保存的值为 ValueType 类型则返回 true。
        ///
        /// \see as
        ///
        //////////////////////////////////////////////////////////////////
        template<class ValueType> bool is() const
        {
            typedef typename std::decay<ValueType>::type T;

            auto derived = std::dynamic_pointer_cast<Derived<T>> (_ptr);

            return derived;
        }

        //////////////////////////////////////////////////////////////////
        /// \brief 取出保存的值并转换为 ValueType 的原始类型。
        ///
        /// 1. 使用 std::decay 将 ValueType 的修饰符（&、const等）抹去，得到原始类型，设为 T。
        /// 2. 尝试将 _ptr 转换为 Derived<T> 类型指针 derived。
        /// 3. 如果成功，则 derived 非空，以 T 类型返回其中包含的值。
        /// 4. 否则说明类型不匹配，抛出 bad_cast 异常。
        ///
        /// \return 实际保存的值。
        ///
        /// \see is
        ///
        //////////////////////////////////////////////////////////////////
        template<class ValueType> typename std::decay<ValueType>::type& as()
        {
            typedef typename std::decay<ValueType>::type T;

            auto derived = std::dynamic_pointer_cast<Derived<T>> (_ptr);

            if (!derived) {
                throw std::bad_cast();
            }

            return derived->value;
        }

        //////////////////////////////////////////////////////////////////
        /// \brief 隐式类型转换操作符。
        ///
        /// 假设 i 为 int 型，a 为 Any 型。则执行 i = a 时会发生隐式类型转换，
        /// 将 Any 型转换为 int。此时会调用本函数，将保存的值通过 as() 函数
        /// 转换为 int 型返回。ValueType 由编译器推导为 int，因而不用手动输入。
        ///
        /// \see as
        ///
        //////////////////////////////////////////////////////////////////
        template<class ValueType> operator ValueType()
        {
            return as<ValueType>();
        }

        //////////////////////////////////////////////////////////////////
        /// \brief 无参数构造函数，生成空对象。
        ///
        //////////////////////////////////////////////////////////////////
        Any()
            : _ptr(nullptr)
        { }

        //////////////////////////////////////////////////////////////////
        /// \brief 拷贝构造函数。
        ///
        //////////////////////////////////////////////////////////////////
        Any(const Any& other)
            : _ptr(other._ptr)
        { }

        //////////////////////////////////////////////////////////////////
        /// \brief 拷贝构造函数。
        ///
        //////////////////////////////////////////////////////////////////
        Any(Any& other)
            : _ptr(other._ptr)
        { }

        //////////////////////////////////////////////////////////////////
        /// \brief 移动构造函数。
        ///
        //////////////////////////////////////////////////////////////////
        Any(Any&& other)
            : _ptr(other._ptr)
        { }

        Any& operator = (const Any& other)
        {
            if (&other != this)
                this->_ptr = other._ptr;
        }

    private:
        //////////////////////////////////////////////////////////////////
        /// \brief 内部类型。
        ///        无内容。用于抹除实际值的具体类型并使用单一类型保存。
        ///
        //////////////////////////////////////////////////////////////////
        struct Base
        {
            virtual ~Base() {}
        };

        //////////////////////////////////////////////////////////////////
        /// \brief 内部类型，用于保存实际值。
        ///
        //////////////////////////////////////////////////////////////////
        template<typename StorageType>
            struct Derived : Base
        {
            //////////////////////////////////////////////////////////////
            /// \brief 构造函数。
            ///
            /// 使用模板参数指定值的实际类型。
            /// std::forward 用于保留参数的修饰符。
            //////////////////////////////////////////////////////////////
            template<typename ValueType>
                Derived(ValueType&& value) : value(std::forward<ValueType>(value)) { }

            StorageType value;  ///< 实际保存的值
        };

        std::shared_ptr<Base> _ptr; ///< 指向包含了实际值的对象的指针
};
