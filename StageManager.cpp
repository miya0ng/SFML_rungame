#include "stdafx.h"
#include "StageManager.h"
#include "Jelly.h"

StageManager::StageManager()
{
}

void StageManager::Init()
{
	tileTexture.loadFromFile("img/Objectimg/map1img/platform1.png");
	tileSprite.setTexture(tileTexture);
	tileSprite.setScale(0.7f, 0.7f);

	jellySpawnTriggerX = FRAMEWORK.GetWindowBounds().width + 100.f;
}

Jelly* StageManager::SpawnJelly()
{
	if (!pooledJellyList.empty())
	{
		jellys = pooledJellyList.back();
		pooledJellyList.pop_back();
	}
	else
	{
		jellys = new Jelly();
	}

	jellys->SetActive(true);
	jellys->Init();
	jellys->SetPosition({ startX, 300 });

	float startJellyX = activeJellyList.empty() ? 0.f : activeJellyList.back()->GetPosition().x + jellys->sprite.getGlobalBounds().width;
	jellys->SetActive(true);
	jellys->Init();
	jellys->SetPosition({ startJellyX, 300 });
	activeJellyList.push_back(jellys);

	//std::cout << jellyPos.x << ", " << jellyPos.y << std::endl;
	return jellys;
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

	float startX = activeTiles.empty() ? 0.f : activeTiles.back()->GetPosition().x + tileSprite.getGlobalBounds().width;

	newTile->SetPosition({ startX, 300 });
	newTile->SetScale({ 0.7f, 0.7f });
	activeTiles.push_back(newTile);

	return newTile;
}

void StageManager::Update(float dt, float playerSpeed)
{
	//====================================================================================SpawnTile
	float tileWidth = tileSprite.getGlobalBounds().width;
	float tileSpawnTriggerX = FRAMEWORK.GetWindowBounds().width - tileWidth;

	for (auto it = activeTiles.begin(); it != activeTiles.end(); )
	{
		auto tile = *it;
		pos = tile->GetPosition();
		pos.x += dt * playerSpeed * dir;
		tile->SetPosition({ pos.x, newTile->GetPosition().y });
		if (pos.x < -tileWidth)//------------------------------------tile->SetActive(false)
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

	//std::cout << activeJellyList.size() << std::endl;
	//====================================================================================SpawnJelly
	for (auto it = activeJellyList.begin(); it != activeJellyList.end(); )
	{
		auto jelly = *it;
		jellyPos = jelly->GetPosition();
		jellyPos.x += dt * jellySpeed;
		jellyPos.y = 250.f;
		jelly->SetPosition(jellyPos);
		//std::cout << jelly->GetPosition().x << ", " << jelly->GetPosition().y << std::endl;
		if (jellyPos.x < -jellys->sprite.getGlobalBounds().width)//------------------------------------jelly->SetActive(false)
		{
			jelly->SetActive(false);
			pooledJellyList.push_back(jelly);
			it = activeJellyList.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (jellyPos.x < jellySpawnTriggerX)
	{
		SpawnJelly();
	}
}

void StageManager::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTiles)
	{
		t->Draw(win);
	}

	for (auto* t : activeJellyList)
	{
		t->Draw(win);
	}
}