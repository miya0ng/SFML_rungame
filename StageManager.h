#pragma once
#include "Platform.h"

class Platform;
class AniPlayer;
class StageManager;	
using TilePattern = std::function<void(StageManager&)>;

struct TimedPattern
{
	float startTime;
	float endTime;
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
	float elapsedTime = 0.f;
	TilePattern currentPattern;

	Platform* newTile = nullptr;
	AniPlayer* aniPlayer = nullptr;
public:
	StageManager();
	float startX = 0.f;
	float lastX = 0.f;
	float tileW = 0.f;
	float baseY = 300.f;
	using TilePattern = std::function<void(StageManager&)>;

	bool NeedNewTiles() const;
	void SetPattern(TilePattern p) { currentPattern = std::move(p); }

	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
	void SpawnPattern(TileType type);

private:
	void MoveTiles(float dt, float playerSpeed);
};