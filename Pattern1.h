#pragma once
#include "GameObject.h"

class Obstacle;
class Jelly;
class Platform;
class AniPlayer;
class Pattern1 :
    public GameObject
{
protected:
	sf::Vector2f tilePos;
	sf::Vector2f jellyPos;
	sf::Vector2f conePos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;

	Platform* tiles = nullptr;
	AniPlayer* aniPlayer = nullptr;
	Jelly* jellys = nullptr;
	Obstacle* cones = nullptr;

	float dir = -1.f;
	float tileSpawnX = 0.f;
	float tileSpawnY = FRAMEWORK.GetWindowBounds().height - 80.f;
	float jellySpawnX = 300.f;
	float jellySpawnY = 220.f;
	float jellySpacing = 50.f;
	float coneSpawnX = 1782.f;
	float coneSpawnY = FRAMEWORK.GetWindowBounds().height - 80.f;

public:
	std::vector<Platform*> activeTileList;
	std::vector<Platform*> pooledTileList;
	std::vector<Obstacle*> activeConeList;
	std::vector<Obstacle*> pooledConeList;
	std::vector<Jelly*> activeJellyList;
	std::vector<Jelly*> pooledJellyList;

	Pattern1();
	~Pattern1();

	void Init();
	void Release();
	void Reset();
	void Update(float dt, float playerSpeed);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};