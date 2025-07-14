#pragma once
#include "Platform.h"

class Platform;
class AniPlayer;
class StageManager
{
protected:
	std::vector<Platform*> activeTiles;
	std::vector<Platform*> pooledTiles;
	sf::Texture basicTile;
	Platform* newTile = nullptr;
	AniPlayer* aniPlayer = nullptr;

public:
	StageManager();

	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
};