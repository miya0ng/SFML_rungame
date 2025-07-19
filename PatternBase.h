#pragma once
#include "GameObject.h"
class Coin;
class Obstacle;
class Jelly;
class Platform;
class AniPlayer;
class PatternBase :
    public GameObject
{
	public:
		virtual void Update(float dt, float playerSpeed) = 0;
		virtual void Draw(sf::RenderWindow& window) override = 0;

        virtual void Init() override {}
        virtual void Release() override {}
        virtual void Reset() override {}

        virtual std::vector<Jelly*>& GetJellies() = 0;
        virtual std::vector<Coin*>& GetCoins() = 0;
        virtual std::vector<Obstacle*>& GetObstacles() = 0;
        virtual bool IsFinished() const = 0;
};

