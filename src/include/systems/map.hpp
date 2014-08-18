#pragma once

class Map {
    public:
        typedef GameEntity** MapGrid;

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

        MapGrid _grid;
        size_t _width, _height, _tile_width, _tile_height;
