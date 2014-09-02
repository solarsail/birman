#pragma once

#include <map>
#include "animation.hpp"
#include "components/component.hpp"
#include "utility.hpp"

class AnimatedSpriteComponent : public Component {
    public:
		typedef std::shared_ptr<sf::Texture> TexturePtr;

        explicit AnimatedSpriteComponent(sf::Time frameTime = sf::seconds(0.1f), bool paused = false, bool looped = true);
        void addAnimation(unsigned index, const AnimationData& animation);
        void setFrameTime(sf::Time time);
        void setState(AniState s);
		void setTexture(TexturePtr t);
        void useAnimation(unsigned index);
        void setLoop(bool loop);

    protected:
        void setFrame(size_t frame);
        void update(sf::Time deltaTime);
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
        sf::Sprite _sprite;
};
