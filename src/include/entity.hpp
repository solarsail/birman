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

//////////////////////////////////////////////////////////////////////
/// \brief 游戏实体类。
///
/// 实现为组件的集合，组件可以在实体中注册属性，或访问其他组件已
/// 注册的属性。
///
//////////////////////////////////////////////////////////////////////
class GameEntity : public std::enable_shared_from_this<GameEntity> {
    public:
        typedef std::function<Any(void)> PropertyCallback;

        //////////////////////////////////////////////////////////////
        /// \brief 构造函数。
        ///
        //////////////////////////////////////////////////////////////
		GameEntity();

        //////////////////////////////////////////////////////////////
        /// \brief 将组件加入实体。
        ///
        /// 调用组件的 registerProperty() 函数注册属性。
        ///
        /// \param c 要加入的组件的智能指针
        ///
        //////////////////////////////////////////////////////////////
        void attachComponent(std::shared_ptr<Component> c);
            
        //////////////////////////////////////////////////////////////
        /// \brief 注册属性。
        ///
        /// 将 std::string 类型的 id 和构造 Any 型对象的回调函数
        /// 插入表中。
        ///
        /// \param id 属性标识
        /// \param callback 回调函数，返回包含属性值的 Any 对象
        ///
        //////////////////////////////////////////////////////////////
        void provideProperty(const std::string& id, PropertyCallback callback);

        //////////////////////////////////////////////////////////////
        /// \brief 获取指定属性的值。
        ///
        /// \param id 属性标识
        ///
        /// \return 属性值
        ///
        //////////////////////////////////////////////////////////////
        Any getProperty(const std::string& id);

    private:
        std::unordered_map<std::string, PropertyCallback> _map; ///< 属性 id 与生成属性值的回调函数对应表
        std::set<std::shared_ptr<Component>> _components;       ///< 组件列表

        friend class Component;
        friend class GameEntityFactory;
};
