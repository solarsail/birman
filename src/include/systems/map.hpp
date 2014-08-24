#pragma once

#include <SFML/Graphics.hpp>

class MapSlice : public sf::Drawable {
public:
	MapSlice(size_t W, size_t H) :
		_vertices(sf::Quads, W * H * 4),
		_width(W), _height(H)
	{ }

private:
	/// 以(x, y)为原点构造顶点数组
	void buildSprite(size_t x, size_t y);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray _vertices;
	size_t _width, _height;
};

class Map {
public:
	typedef unsigned char** TerrainGrid;
	typedef unsigned char** EffectGrid;

	~Map();

	void load(const std::string& mapname);
#ifdef DEBUG
	void loadTestGrid();
#endif
	size_t width();
	size_t height();
	size_t tileWidth();
	size_t tileHeight();

private:
	void allocate(size_t w, size_t h);
	void erase();

	TerrainGrid _grid;
	size_t _width, _height, _tile_width, _tile_height;
	sf::Texture _tileSetTexture;

	friend class MapSlice;
};