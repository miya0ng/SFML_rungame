#pragma once
#include "PatternBase.h"
class Coin;
class Obstacle;
class Jelly;
class Platform;
class AniPlayer;
class Pattern2 :
	public PatternBase
{
protected:
	sf::Vector2f tilePos;
	sf::Vector2f jellyPos;
	sf::Vector2f conePos;
	sf::Vector2f coinPos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;

	Platform* tiles = nullptr;
	AniPlayer* aniPlayer = nullptr;
	Jelly* jellys = nullptr;
	Obstacle* cones = nullptr;
	Coin* coins = nullptr;

	float dir = -1.f;
	float tileSpawnX = 0.f;
	float tileSpawnY = FRAMEWORK.GetWindowBounds().height - 80.f;
	float jellySpawnX = 300.f;
	float jellySpawnY = 220.f;
	float coinSpawnX = 350.f;
	float coinSpawnY = 220.f;
	float jellySpacing = 50.f;
	float coneSpawnX = 1782.f;
	float coneSpawnY = FRAMEWORK.GetWindowBounds().height - 79.f;

public:
	std::vector<Platform*> activeTileList;
	std::vector<Platform*> pooledTileList;
	std::vector<Obstacle*> activeConeList;
	std::vector<Obstacle*> pooledConeList;
	std::vector<Jelly*> activeJellyList;
	std::vector<Jelly*> pooledJellyList;
	std::vector<Coin*> activeCoinList;
	std::vector<Coin*> pooledCoinList;

	Pattern2();
	~Pattern2();

	void Init();
	void Release();
	void Reset();
	void Update(float dt, float playerSpeed);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	std::vector<Jelly*>& GetJellies() override { return activeJellyList; }
	std::vector<Coin*>& GetCoins() override { return activeCoinList; }
	std::vector<Obstacle*>& GetObstacles() override { return activeConeList; }
	bool IsFinished() const {
		return activeTileList.empty();
	}
};