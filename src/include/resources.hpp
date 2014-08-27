#pragma once

#include <cassert>
#include <cstdint>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

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

	TestSP,
    // ...
};


template <typename Resource, typename ID>
class TextureHolder {
    public:
        void load(ID id, const std::string& filename);
        template <typename Param>
        void load(ID id, const std::string& filename, const Param& p);
        Resource& get(ID id);
        const Resource& get(ID id) const;
        
    private:
        void insert_resource(ID id, std::shared_ptr<Resource> res);

    private:
        std::map<ID, std::shared_ptr<Resource>> _texture_map;
};


#include "resources.inl"
