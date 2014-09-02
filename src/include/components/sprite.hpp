#include "components/component.hpp"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component {
    public:
		typedef std::shared_ptr<sf::Texture> TexturePtr;

        SpriteComponent();

		void setTexture(TexturePtr t);
        sf::Vector2f getPosition() const;

    protected:
        void bindListeners() override;
        void registerProperties() override;

    private:
        sf::Sprite _sprite;
};

bool operator <(const SpriteComponent& a, const SpriteComponent& b);
