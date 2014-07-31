#pragma once

#include <memory>
#include <type_traits>

class Component;

//////////////////////////////////////////////////////////////////////
/// \brief 组件工厂类。
///
/// 用于生成指定类型的组件。
///
//////////////////////////////////////////////////////////////////////
class ComponentFactory {
    public:

        //////////////////////////////////////////////////////////////
        /// \brief 创建 T 类型的组件。
        ///
        /// 使用 std::is_base_of 判断 T 是否为组件类型，
        /// 并使用 static_assert 使错误类型无法通过编译。
        ///
        /// \return 指向指定组件类型对象的智能指针
        //////////////////////////////////////////////////////////////
        template <class T> std::shared_ptr<T> create()
        {
            static_assert(std::is_base_of<Component, T>::value, "Attempt to instantiate non Component derived classes");
            return std::make_shared<T>();
        }
};
