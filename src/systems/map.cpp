#include <cstring>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "systems/map.hpp"

MapSlice::MapSlice(size_t W, size_t H, Map& map) :
	_vertices(sf::Quads, W * H * 4),
	_width(W), _height(H), _map(map), _texture(map._tileSetTexture)
{
}

void MapSlice::buildDrawable(size_t x, size_t y)
{
	size_t tileWidth = _map.tileWidth();
	size_t tileHeight = _map.tileHeight();

    size_t dx = x * tileWidth;
    size_t dy = y * tileHeight;

	// find its position in the tileset texture

	for (int i = 0; i < _height/* rows */; ++i)
		for (int j = 0; j < _width/* cols */; ++j) {
			int tileNumber = _map._grid[(x + j) + (y + i) * _width];
			int tu = tileNumber % (_texture.getSize().x / tileWidth);
			int tv = tileNumber / (_texture.getSize().x / tileWidth);

			sf::Vertex* quad = &_vertices[(i * _width + j) * 4];

			quad[0].position = sf::Vector2f(dx + j * tileWidth, dy + i * tileHeight);
			quad[1].position = sf::Vector2f(dx + (j + 1) * tileWidth, dy + i * tileHeight);
			quad[2].position = sf::Vector2f(dx + (j + 1) * tileWidth, dy + (i + 1) * tileHeight);
			quad[3].position = sf::Vector2f(dx + j * tileWidth, dy + (i + 1) * tileHeight);

			quad[0].texCoords = sf::Vector2f(tu * tileWidth, tv * tileHeight);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileWidth, tv * tileHeight);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileWidth, (tv + 1) * tileHeight);
			quad[3].texCoords = sf::Vector2f(tu * tileWidth, (tv + 1) * tileHeight);
		}
}

void MapSlice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &_texture;

	// draw the vertex array
	target.draw(_vertices, states);
}

///////////////////////////////////////////////////////
// Map
///////////////////////////////////////////////////////

Map::Map() :
	_grid(nullptr),
	_width(0), _height(0),
	_tileWidth(0), _tileHeight(0)
{}

Map::Map(Map&& m) :
	_grid(m._grid), _tileSetTexture(m._tileSetTexture),
	_width(m._width), _height(m._height),
	_tileWidth(m._tileWidth), _tileHeight(m._tileHeight)
{
	m._grid = nullptr;
	// reset texture
}

Map& Map::operator=(Map&& m)
{
    if (&m == this)
        return *this;
    _grid = m._grid;
    _tileSetTexture = m._tileSetTexture;
    _width = m._width;
    _height = m._height;
    _tileWidth = m._tileWidth;
    _tileHeight = m._tileHeight;
    m._grid = nullptr;
}

Map::~Map()
{
	delete[] _grid;
}

size_t Map::width() { return _width; }

size_t Map::height() { return _height; }

size_t Map::tileWidth() { return _tileWidth; }

size_t Map::tileHeight() { return _tileHeight; }

void Map::allocate(size_t w, size_t h)
{
	_grid = new TerrainCell[w * h];
}

void Map::erase()
{
	delete[] _grid;
}

///////////////////////////////////////////////////////
// MapLoader
///////////////////////////////////////////////////////

Map MapLoader::load(const std::string& mapname)
{
	// not implemented
	return Map();
}

Map MapLoader::loadTestMap()
{
	const Map::TerrainCell grid[] = 
	{
		9, 9, 9, 9, 9, 9, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
		9, 29, 29, 29, 29, 29, 29, 9, 9, 9, 9, 31, 9, 9, 9, 9,
		29, 29, 9, 9, 9, 9, 9, 9, 14, 14, 14, 14, 14, 14, 14, 14,
		9, 29, 9, 9, 31, 9, 14, 14, 14, 9, 29, 29, 29, 9, 9, 9,
		9, 29, 29, 9, 14, 14, 14, 9, 9, 9, 29, 29, 29, 31, 9, 9,
		9, 9, 29, 9, 14, 9, 31, 31, 9, 9, 29, 29, 29, 29, 31, 9,
		31, 9, 29, 9, 14, 9, 31, 31, 31, 9, 29, 29, 29, 29, 29, 29,
		9, 9, 29, 9, 14, 31, 31, 31, 9, 9, 9, 9, 29, 29, 29, 29,
	};

	Map map;
	map.allocate(16, 8);
	map._tileWidth = 32;
	map._tileHeight = 32;
	memcpy(map._grid, grid, 16 * 8);
	sf::Texture tileset;
	if (!map._tileSetTexture.loadFromFile("../assets/textures/desert-compact.png"))
		throw std::runtime_error("unable to load texture");

	return map;
}
