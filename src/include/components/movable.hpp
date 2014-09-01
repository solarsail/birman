#pragma once

#include <SFML/Graphics.hpp>
#include "components/component.hpp"
#include "utility.hpp"

class MovableComponent : public Component {
    public:
        MovableComponent();
        void setSpeed(float pixels);
        void setDirection(Direction d);
        void setVelocity(sf::Vector2f v);
        void setMovementTime(sf::Time t);
        float getSpeed();
        Direction getDirection();
        sf::Vector2f getVelocity();
        sf::Time getMovementTime();


    protected:
        void registerProperties() override;

        float _speed;
        Direction _direction;
        sf::Vector2f _velocity;
        sf::Time _timeDelta;
};
