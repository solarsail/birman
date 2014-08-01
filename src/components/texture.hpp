#include "components/component.hpp"

namespace sf { class Texture; }

class TextureComponent : public Component {
    public:
        typedef std::shared_ptr<sf::Texture> TexturePtr;

        TextureComponent(TexturePtr texture);

    protected:
        TexturePtr getUpdatedTexture();
        void registerProperty(std::shared_ptr<GameEntity> entity) override;

    private:
        TexturePtr _texture;
};
