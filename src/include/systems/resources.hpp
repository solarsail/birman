#pragma once

#include <cassert>
#include <cstdint>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <SFML/Graphics.hpp>

enum class TextureID : std::uint8_t
{
    None = 0,

    // Ground Tiles
    Grass,
    Desert,
    Dirt,
    Stone,

    // Floor Tiles
    Floor_wood,
    Floor_stone,
    Floor_marble,

    // Wall Tiles
    Wall_wood_left,
    Wall_wood_right,

	TestPlayer,
	TestMap,
    // ...
};


template <typename Resource, typename ID>
class ResourceHolder {
    public:
		typedef std::shared_ptr<Resource> ResPtr;

		static ResourceHolder<Resource, ID>& get();
        void load(ID id, const std::string& filename);
        template <typename Param>
        void load(ID id, const std::string& filename, const Param& p);
        ResPtr get(ID id);
        const ResPtr get(ID id) const;
        
    private:
		ResourceHolder();
		ResourceHolder(const ResourceHolder<Resource, ID>&);
		ResourceHolder<Resource, ID>& operator=(const ResourceHolder<Resource, ID>&);
        void insert_resource(ID id, ResPtr res);

    private:
        std::map<ID, ResPtr> _resource_map;
};

typedef ResourceHolder<sf::Texture, TextureID> TextureHolder;


#include "resources.inl"
