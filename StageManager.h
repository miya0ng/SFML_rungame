#pragma once
#include "Platform.h"

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

public:
	StageManager();
	float startX = 0.f;
	float lastX = 0.f;
	float tileW = tileSprite.getGlobalBounds().width;
	float baseY = 300.f;
	using TilePattern = std::function<void(StageManager&)>;

	bool NeedNewTiles() const;

	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
	Platform* SpawnPattern(TileType type);
	void MoveTiles(float dt, float playerSpeed);
};