#pragma once

#include <functional>
#include <memory>
#include "entity.hpp"

namespace Property {
    static const char* WorldPosition = "WorldPos";
    static const char* WorldZ = "WorldZ";
    static const char* Sprite = "Sprite";
}

class ComponentFactory;

//////////////////////////////////////////////////////////////////////
/// \brief 组件的基类。
///
/// 派生类应重写 registerProperty() 函数，向实体注册所提供的属性。
///
//////////////////////////////////////////////////////////////////////
class Component {
	public:
		Component();
		virtual ~Component();

	protected:
		//////////////////////////////////////////////////////////////
		/// \brief 向实体注册本组件所需要监听的属性。
		///
		/// 应只被GameEntity::attachComponent()函数调用。
		/// GameEntity::attachComponent()函数保证了此函数调用之前
		/// _entity变量已经被设置。
		//////////////////////////////////////////////////////////////
		virtual void bindListeners();

		//////////////////////////////////////////////////////////////
		/// \brief 向实体注册本组件提供的属性。
		///
		/// 应只被GameEntity::attachComponent()函数调用。
		/// GameEntity::attachComponent()函数保证了此函数调用之前
		/// _entity变量已经被设置。
		//////////////////////////////////////////////////////////////
		virtual void registerProperties();

		//////////////////////////////////////////////////////////////
		/// \brief 设置本组件所加入的实体。
		///
		/// \param entity 所属实体的智能指针
		///
		//////////////////////////////////////////////////////////////
		void setEntity(GameEntityPtr entity);

		GameEntityPtr _entity;    ///< 指向所属实体的智能指针

		friend class ComponentFactory;
		friend class GameEntity;
};
