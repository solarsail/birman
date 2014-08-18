#include "map.hpp"


void Map::load(const std::string& mapname)
{
}

#ifdef DEBUG
void Map::loadTestGrid()
{
    auto c = ComponentFactory::create<SpriteComponent>();
    c.load("test.png");
    this->allocate(500, 500);
    for (int i = 0; i < 500; ++i)
        for (int j = 0; j < 500; ++j)
            _grid[i][j].attachComponent(c);
}
#endif

size_t Map::width() { return _width; }

size_t Map::height() { return _height; }

size_t Map::tileWidth() { return _tile_width; }

size_t Map::tileHeight() { return _tile_height; }

void Map::allocate(size_t w, size_t h)
{
    _grid = new GameEntity[w * h];
}

void Map::erase()
{
    delete[] _grid;
}
