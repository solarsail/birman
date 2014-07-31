#pragma once

#include <functional>
#include <memory>
#include "entity.hpp"

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
        /// \brief 向实体注册本组件提供的属性。
        ///
        /// \param entity 所属实体的智能指针
        ///
        //////////////////////////////////////////////////////////////
        virtual void registerProperty(std::shared_ptr<GameEntity> entity);

    private:
        std::shared_ptr<GameEntity> _entity;    ///< 指向所属实体的智能指针

        friend class ComponentFactory;
        friend class GameEntity;
};
