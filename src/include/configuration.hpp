#pragma once

#include <map>
#include <string>
#include "any.hpp"

enum class ConfigItem {
	WindowWidth,
	WindowHeight,
	WindowTitle,
	MapName,
};

class Configuration {
	public:
		template<typename T>
		void set(ConfigItem item, T value)
		{
			_map.insert(std::make_pair(item, value));
		}

		Any get(ConfigItem item) const
		{
			return _map.at(item);
		}

	private:
		std::map<ConfigItem, Any> _map;
};
