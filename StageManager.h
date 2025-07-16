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
	sf::Vector2f jellyPos;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	
	float dir = -1.f;

	Platform* newTile = nullptr;
	AniPlayer* aniPlayer = nullptr;


	Jelly* jellys = nullptr;
	int jellyCount = 400;
	float jellySpeed = -0.f;
	//float jellySpawnX = FRAMEWORK.GetWindowSizeF().x + 100.f;
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

	std::vector<Jelly*>& GetActiveJellyList()
	{
		return activeJellyList;
	}
	Jelly* SpawnJelly();
	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
	//Platform* SpawnPattern(TileType type);

	const std::vector<Jelly*>& GetActiveJellies() const { return activeJellyList; }
};