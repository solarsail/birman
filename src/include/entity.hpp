#pragma once

#include <cassert>
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "any.hpp"
#include "category.hpp"



class Component;
class GameEntityFactory;
class Command;


//////////////////////////////////////////////////////////////////////
/// \brief 游戏实体类。
///
/// 实现为组件的集合，组件可以在实体中注册属性，或访问其他组件已
/// 注册的属性。
///
//////////////////////////////////////////////////////////////////////
class GameEntity : public std::enable_shared_from_this<GameEntity> {
	public:
		typedef std::function<Any(void)> ValueProvider;
		typedef std::function<void(Any)> ValueConsumer;

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
		/// \brief 当属性变化时通知其他组件。
		///
		/// 使用属性的新值依次调用所有注册在属性名下的监听函数。
		/// 属性的新值通过属性值提供函数获取。
		///
		/// \param id 属性标识
		/// \param value 属性的新值
		///
		//////////////////////////////////////////////////////////////
		void notify(const std::string& id);
			
		//////////////////////////////////////////////////////////////
		/// \brief 注册属性监听函数。
		///
		/// 将 std::string 类型的 id 和以 Any 型对象为参数的监听函数
		/// 插入表中。
		///
		/// \param id 属性标识
		/// \param function 监听函数，参数为 Any 对象，无返回值
		///
		//////////////////////////////////////////////////////////////
		void listen(const std::string& id, ValueConsumer function);

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
		void provideProperty(const std::string& id, ValueProvider callback);

		//////////////////////////////////////////////////////////////
		/// \brief 获取指定属性的值。
		///
		/// \param id 属性标识
		///
		/// \return 属性值
		///
		//////////////////////////////////////////////////////////////
		Any getProperty(const std::string& id);

		//////////////////////////////////////////////////////////////
		/// \brief 处理消息系统传递过来的指令。
		///
		/// 函数判断传递过来的指令与category是否符合，若该category属于command
		/// 指令范围内，则执行action
		/// 
		/// \param command 事件指令
		//////////////////////////////////////////////////////////////
		void onCommand(const Command& command);

	private:
		std::unordered_map<std::string, std::pair<ValueProvider, std::vector<ValueConsumer>>> _bindings; ///< 属性 id、属性值获取函数与属性监听函数列表
		std::set<std::shared_ptr<Component>> _components;       ///< 组件列表
		Category::Type _category;                               ///< 实体类型

		friend class Component;
		friend class GameEntityFactory;
};
