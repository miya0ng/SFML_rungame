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
	Platform* tile = nullptr;
	AniPlayer* aniPlayer = nullptr;

	sf::Vector2f tilePos = { 0,0 };	

public:
	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
};

