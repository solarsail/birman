#include "components/component.hpp"
#include <SFML/Graphics.hpp>

namespace sf { class Sprite; }

class SpriteComponent : public Component {
    public:
        typedef std::shared_ptr<sf::Sprite> SpritePtr;

        SpriteComponent(SpritePtr sprite);
        SpriteComponent(const std::string& id);
        SpriteComponent();

        sf::Vector2f getCenter();

    protected:
        void bindListeners() override;
        void registerProperties() override;

    private:
        SpritePtr _sprite;
};

bool operator <(const SpriteComponent::SpritePtr& a, const SpriteComponent::SpritePtr& b);
