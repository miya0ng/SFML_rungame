#include "stdafx.h"
#include "StageManager.h"

StageManager::StageManager()
{
}

void StageManager::Init()
{
	
}

Platform* StageManager::SpawnTile(TileType type)
{
	newTile = nullptr;

	if (!pooledTiles.empty())
	{
		newTile = pooledTiles.back();
		pooledTiles.pop_back();
	}
	else
	{
		newTile = new Platform();
	}

	newTile->SetActive(true);
	newTile->Init();
	newTile->SetType(type);

	float startX = activeTiles.empty() ? 1000.f : activeTiles.back()->GetPosition().x + activeTiles.back()->GetGlobalBounds().width;

	newTile->SetPosition({ startX, 300 });

	activeTiles.push_back(newTile);
	return newTile;
}

void StageManager::Update(float dt, float playerSpeed)
{
	float tileSpawnTriggerX = newTile->GetPosition().x + 800.f;

	if (!activeTiles.empty())
	{
		float lastTileX = activeTiles.back()->GetPosition().x;
		float lastTileWidth = activeTiles.back()->GetGlobalBounds().width;

		if (lastTileX < tileSpawnTriggerX)
		{
			SpawnTile(TileType::Ground);
		}
	}
	else
	{
		SpawnTile(TileType::Ground);
	}
}


void StageManager::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTiles)
		t->Draw(win);
}