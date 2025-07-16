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
	sf::Vector2f tilePos;
	sf::Vector2f jellyPos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	
	float dir = -1.f;

	Platform* newTile = nullptr;
	AniPlayer* aniPlayer = nullptr;


	Jelly* jellys = nullptr;

	float jellySpeed = -0.f;
	float jellySpawnX =0.f;
	float jellySpawnY = 300.f;
	float jellySpacing = 15.f;

public:
	std::vector<Jelly*> activeJellyList;
	std::vector<Jelly*> pooledJellyList;

	StageManager(std::vector<Jelly*>& active, std::vector<Jelly*>& pooled);
	~StageManager();
	float startX = 0.f;
	float lastX = 0.f;
	float tileW = tileSprite.getGlobalBounds().width;
	float baseY = 300.f;

	using TilePattern = std::function<void(StageManager&)>;

	const std::vector<Jelly*>& GetActiveJellies() const { return activeJellyList; }
	std::vector<Jelly*>& GetActiveJellyList()
	{
		return activeJellyList;
	}

	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);

	Jelly* SpawnJelly();
	void SetTile(float dt, float playerSpeed);
	void SetP1(float dt, float playerSpeed);
	void SetP2(float dt, float playerSpeed);
	void SetP3(float dt, float playerSpeed);
	void SetP4(float dt, float playerSpeed);

};