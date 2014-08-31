#pragma once

#include <SFML/Graphics.hpp>

class Map;

class MapSlice : public sf::Drawable, public sf::Transformable {
	public:
		MapSlice(size_t W, size_t H, Map& map);
		~MapSlice();

		sf::FloatRect reloadBound(sf::Vector2f viewsize);

		/// 以(x, y)为原点构造顶点数组
		void buildDrawable(size_t x, size_t y);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::VertexArray* _vertices;
		size_t _width, _height;
		sf::FloatRect _availSize;
		Map& _map;
		sf::Texture _texture;
};

class Map {
	public:
		typedef unsigned char TerrainCell;
		typedef TerrainCell* TerrainGrid;
		typedef unsigned char* EffectGrid;

		Map();
		Map(Map&& m);
		~Map();
        Map& operator=(Map&& m);

		void allocate(size_t w, size_t h);

		size_t width();
		size_t height();
		size_t tileWidth();
		size_t tileHeight();

	private:
		void erase();

		TerrainGrid _grid;
		size_t _width;
		size_t _height;
		size_t _tileWidth;
	    size_t _tileHeight;
		sf::Texture _tileSetTexture;

		friend class MapSlice;
		friend class MapLoader;
};

class MapLoader {
	public:
		static Map loadTestMap();
		static Map load(const std::string& mapname);
};
