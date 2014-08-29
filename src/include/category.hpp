#pragma once

#include <bitset>

//////////////////////////////////////////////////////////////////////
/// \brief 游戏实体类枚举，每定义一种新的GameEntity，
///        应该把该GameEntity类型添加到枚举中
///
//////////////////////////////////////////////////////////////////////
namespace Category
{
	enum Type
	{
		Player = 0,
		Tree,
		Animal,

		// 放在最后
		TypeCount
	};
}

//////////////////////////////////////////////////////////////////////
/// \brief 游戏实体类型集合
///
//////////////////////////////////////////////////////////////////////
class CategorySet {
	public:
		//////////////////////////////////////////////////////////////
		/// \brief 判断集合中是否包含 type 类型。
		///
		/// \param type 要判断的类型
		///
		/// \return 包含则返回 true，否则返回 false。
		///
		//////////////////////////////////////////////////////////////
		bool hasType(Category::Type type) const;

		//////////////////////////////////////////////////////////////
		/// \brief 向集合中添加 type 类型。
		///
		/// \param type 要添加的类型
		///
		//////////////////////////////////////////////////////////////
		void addType(Category::Type type);

		//////////////////////////////////////////////////////////////
		/// \brief 从集合中移出 type 类型。
		///
		/// \param type 要移除的类型
		///
		//////////////////////////////////////////////////////////////
		void removeType(Category::Type type);
		//////////////////////////////////////////////////////////////
		/// \brief 设置command掩码
		///
		/// \param mask 掩码，其中必须是0或1组成的字符串
		///
		//////////////////////////////////////////////////////////////
		void CategorySet::setTypes(std::string mask);

	private:
		std::bitset<Category::TypeCount> _typeSet;  ///< 集合的位图
};
