#include "components/component.hpp"

namespace sf { class Sprite; }

class SpriteComponent : public Component {
    public:
        typedef std::shared_ptr<sf::Sprite> SpritePtr;

        SpriteComponent(SpirtePtr sprite);

    protected:
        sf::Sprite getUpdatedSprite();
        void registerProperty(std::shared_ptr<GameEntity> entity) override;

    private:
        SpritePtr _sprite;
};
