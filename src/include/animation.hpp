#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class AnimationData {
    public:
        AnimationData();
        AnimationData(std::vector<sf::IntRect>&& frames);

        void addFrame(sf::IntRect rect);
        void setFrames(std::vector<sf::IntRect>&& frames);
        //void setSpriteSheet(const sf::Texture& texture);
        //const sf::Texture* getSpriteSheet() const;
        size_t frameCount() const;
        const sf::IntRect& getFrame(size_t n) const;

    private:
        std::vector<sf::IntRect> _frames;
        //const sf::Texture* _texture;
};
