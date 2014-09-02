#pragma once

#include <map>
#include "animation.hpp"
#include "components/component.hpp"
#include "utility.hpp"

class AnimatedSpriteComponent : public Component, public sf::Drawable, public sf::Transformable {
    public:

        explicit AnimatedSpriteComponent(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true);
        void addAnimation(unsigned index, const AnimationData& animation);
        void setFrameTime(sf::Time time);
        void setState(AniState s);
        void setTexture(std::shared_ptr<sf::Texture> t);
        void useAnimation(unsigned index);
        void setLoop(bool loop);

        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;

    protected:
        void setFrame(size_t frame);
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void registerProperties() override;
        void bindListeners() override;

    private:
        std::map<unsigned, AnimationData> _animations;
        AnimationData* _currentAni;
        sf::Time _frameTime;
        sf::Time _currentTime;
        size_t _currentFrame;
        bool _paused;
        bool _looped;
        std::shared_ptr<sf::Texture> _texture;
        sf::Vertex _vertices[4];
};
