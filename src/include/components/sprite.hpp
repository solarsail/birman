#include "components/component.hpp"

namespace sf { class Sprite; }

class SpriteComponent : public Component {
    public:
        typedef std::shared_ptr<sf::Sprite> SpritePtr;

        SpriteComponent(SpirtePtr sprite);
        SpriteComponent(const std::string& id);
        SpriteComponent();

        sf::Vector2f getCenter();

    protected:
        void bindListeners() override;

    private:
        SpritePtr _sprite;
};

bool operator <(const SpriteComponent::SpritePtr& a, const SpriteComponent::SpritePtr& b);
