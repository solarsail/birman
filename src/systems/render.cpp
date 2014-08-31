#include "components/component.hpp"
#include "systems/render.hpp"

RenderSystem& RenderSystem::get()
{
    static RenderSystem instance;
    return instance;
}

RenderSystem::RenderSystem() { }
RenderSystem::~RenderSystem() 
{
    if (_mapSlicePtr)
        delete _mapSlicePtr;
}

void RenderSystem::setMap(Map& map)
{
    _terrainPtr = &map;
}

void RenderSystem::init(GameContext& ctx, EntityPtr player)
{
    sf::View& view = ctx.mainView;
	auto viewsize = view.getSize();
    _player = player;
    _lastCenter = _player->getProperty(Property::WorldPosition);
    view.setCenter(_lastCenter);
	// 预加载view四倍尺寸的地图块
    _mapSlicePtr = new MapSlice(viewsize.x * 4 / _terrainPtr->tileWidth(), viewsize.y * 4 / _terrainPtr->tileHeight(), *_terrainPtr);
    reloadMapSlice(_lastCenter - view.getSize() * 2.f);
	_reloadBound = _mapSlicePtr->reloadBound(viewsize);
}

void RenderSystem::process(GameContext& ctx)
{
    sf::View& view = ctx.mainView;
    sf::Vector2f center = _player->getProperty(Property::WorldPosition);
    if (!_reloadBound.contains(center)) {
        reloadMapSlice(center - view.getSize() / 2.f);
        view.setCenter(center);
    } else {
        view.move(center - _lastCenter);
        _lastCenter = center;
    }

    // Render
    ctx.window.clear();
    ctx.window.setView(view);
    ctx.window.draw(*_mapSlicePtr);
    // TODO: draw objects, player, etc.
    ctx.window.display();
}

void RenderSystem::reloadMapSlice(sf::Vector2f origin)
{
    // if (没有到达边界)
    int x = origin.x / _terrainPtr->tileWidth();
    int y = origin.y / _terrainPtr->tileHeight();

    if (x < 0) x = 0;
    if (y < 0) y = 0;

    _mapSlicePtr->buildDrawable(x, y);
}

void RenderSystem::registerObject(EntityPtr object)
{
    _objects.insert(object);
}

void RenderSystem::unregisterObject(EntityPtr object)
{
    _objects.erase(object);
}
