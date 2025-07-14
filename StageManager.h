#pragma once
#include "Platform.h"

class Platform;
class AniPlayer;
class StageManager
{
protected:
	std::vector<Platform*> activeTiles;
	std::vector<Platform*> pooledTiles;
	sf::Vector2f pos;
	float dir = -1.f;
	Platform* newTile = nullptr;
	AniPlayer* aniPlayer = nullptr;
	sf::Texture tileTexture;
	sf::Sprite tileSprite;
	
public:
	StageManager();

	Platform* SpawnTile(TileType type);
	void Init();
	void Update(float dt, float playerSpeed);
	void Draw(sf::RenderWindow& window);
};