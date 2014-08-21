#include "category.hpp"

bool CategorySet::hasType(Category::Type type)
{
	return _typeSet.test(type);
}

void CategorySet::addType(Category::Type type)
{
	_typeSet.set(type);
}

void CategorySet::removeType(Category::Type type)
{
	_typeSet.reset(type);
}
void CategorySet::setTypes(std::string mask)
{
	std::bitset<Category::TypeCount> tmp(mask);
	_typeSet = tmp;
}
