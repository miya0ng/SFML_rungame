#pragma once
#include "Platform.h"

class Jelly;
class Platform;
class AniPlayer;
class StageManager;	
using TilePattern = std::function<void(StageManager&)>;

struct TimedPattern
{
	float startTime=0.f;
	float endTime=0.f;
	TilePattern pattern;
};

class StageManager
{
protected:
	std::vector<Platform*> activeTiles;
	std::vector<Platform*> pooledTiles;
	sf::Vector2f pos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	
	float dir = -1.f;

	Platform* newTile = nullptr;
	AniPlayer* aniPlayer = nullptr;

	std::vector<Jelly*>& activeJellyList;
	std::vector<Jelly*>& pooledJellyList;

	Jelly* jellys = nullptr;
	float jellySpeed = -0.f;
	float jellySpawnTriggerX = 0.f;
	bool jellySpawned = false;
	sf::Vector2f jellyPos = { 0.f,100.f };

public:
	StageManager(std::vector<Jelly*>& active, std::vector<Jelly*>& pooled);
	float startX = 0.f;
	float lastX = 0.f;
	float tileW = tileSprite.getGlobalBounds().width;
	float baseY = 300.f;
	using TilePattern = std::function<void(StageManager&)>;

	std::vector<Jelly*>& GetActiveJellyList()
	{
		return activeJellyList;
	}
	Jelly* SpawnJelly();
	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
	Platform* SpawnPattern(TileType type);
	void MoveTiles(float dt, float playerSpeed);
};