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

	//float startX = activeTiles.empty() ? 1000.f : activeTiles.back()->GetPosition().x + activeTiles.back()->GetGlobalBounds().width;
	float startX = activeTiles.empty() ? 0.f : activeTiles.back()->GetPosition().x + 124.f;

	newTile->SetPosition({ startX, 300 });
	activeTiles.push_back(newTile);

	return newTile;
}

void StageManager::Update(float dt, float playerSpeed)
{
	//float tileWidth= newTile->GetGlobalBounds().width;
	float tileWidth= 124.f;
	float tileSpawnTriggerX = FRAMEWORK.GetWindowBounds().width - tileWidth;

	for (auto it = activeTiles.begin(); it != activeTiles.end(); )
	{
		auto tile = *it;
		 pos = tile->GetPosition();
		pos.x += dt * playerSpeed * dir;
		tile->SetPosition({ pos.x, newTile->GetPosition().y});
		if (pos.x < -tileWidth)
		{
			tile->SetActive(false);
			pooledTiles.push_back(tile);
			it = activeTiles.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (pos.x < tileSpawnTriggerX)
	{
		SpawnTile(TileType::Ground);
	}
	
}


void StageManager::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTiles)
		t->Draw(win);
}