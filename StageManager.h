#pragma once
#include "Platform.h"

class Obstacle;
class Jelly;
class Platform;
class AniPlayer;
class StageManager
{
protected:
	std::vector<Platform*> activeTileList;
	std::vector<Platform*> pooledTileList;

	std::vector<Obstacle*> activeCornList;
	std::vector<Obstacle*> pooledCornList;

	sf::Vector2f tilePos;
	sf::Vector2f jellyPos;
	sf::Vector2f cornPos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	
	Platform* tiles = nullptr;
	AniPlayer* aniPlayer = nullptr;
	Jelly* jellys = nullptr;
	Obstacle* corns = nullptr;

	float dir = -1.f;
	float tileSpawnX = 0.f;
	float tileSpawnY = FRAMEWORK.GetWindowBounds().height - tileTexture.getSize().y;
	float jellySpeed = -0.f;
	float jellySpawnX = 300.f;
	float jellySpawnY = 300.f;
	float jellySpacing = 15.f;

	float cornSpawnX = 5493.f;
	float cornSpawnY = 350.f;

public:
	std::vector<Jelly*> activeJellyList;
	std::vector<Jelly*> pooledJellyList;

	StageManager(std::vector<Jelly*>& active, std::vector<Jelly*>& pooled);
	~StageManager();

	const std::vector<Jelly*>& GetActiveJellies() const { return activeJellyList; }
	std::vector<Jelly*>& GetActiveJellyList()
	{
		return activeJellyList;
	}

	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);

	void SetP1(float dt, float playerSpeed);
	void SetP2(float dt, float playerSpeed);
	void SetP3(float dt, float playerSpeed);
	void SetP4(float dt, float playerSpeed);

};