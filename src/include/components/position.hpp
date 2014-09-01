#pragma once

#include <SFML/Graphics.hpp>
#include "components/component.hpp"

class PositionComponent : public Component {
    public:
        void setWorldPos(float x, float y);
        void setWorldPos(const sf::Vector2f& pos);
        sf::Vector2f getWorldPos() const;

        void setWorldZ(float z);
        float getWorldZ() const;

    protected:
		void registerProperties() override;
        void bindListeners() override;

    private:
        sf::Vector2f _world_pos;
        float _z;
        bool _use_lighting;
};
