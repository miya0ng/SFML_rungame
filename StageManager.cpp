#include "stdafx.h"
#include "StageManager.h"
#include "Jelly.h"

StageManager::StageManager(std::vector<Jelly*>& active, std::vector<Jelly*>& pooled)
	:startX(0.f), jellys(nullptr), newTile(nullptr), jellySpeed(100.f), dir(1), activeJellyList(active),
	pooledJellyList(pooled)
{
}

StageManager::~StageManager()
{
	for (auto it : pooledJellyList)
		delete it;
	for (auto it : activeJellyList)
		delete it;
	activeJellyList.clear();
	pooledJellyList.clear();
}

void StageManager::Init()
{
	tileTexture.loadFromFile("img/Objectimg/map1img/platform1.png");
	tileSprite.setTexture(tileTexture);
	tileSprite.setScale(0.7f, 0.7f);

	jellys = new Jelly();
	//for (int i = 0; i < jellyCount; ++i)
	//{
	//	jellys = new Jelly();
	//	jellys->SetPosition({ jellySpawnX, jellySpawnY });
	//	activeJellyList.push_back(jellys);
	//}
}

void StageManager::Update(float dt, float playerSpeed)
{
	//====================================================================================SpawnTile
	float tileWidth = tileSprite.getGlobalBounds().width;
	float tileSpawnTriggerX = FRAMEWORK.GetWindowBounds().width - tileWidth;

	for (auto it = activeTiles.begin(); it != activeTiles.end(); )
	{
		auto tile = *it;
		tilePos = tile->GetPosition();
		tilePos.x += dt * playerSpeed *-dir;
		tile->SetPosition({ tilePos.x, tile->GetPosition().y });
	
		if (tilePos.x < -tileWidth)//------------------------------------tile->SetActive(false)
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
	if (tilePos.x < tileSpawnTriggerX)
	{
		SpawnTile(TileType::Ground);
	}

	//std::cout << activeJellyList.size() << std::endl;
	//====================================================================================SpawnJelly
	float jellyWidth = jellys->GetSprite().getGlobalBounds().width;
	float jeyllSpawnTriggerX = FRAMEWORK.GetWindowBounds().width - jellyWidth;
	for (auto it = activeJellyList.begin(); it != activeJellyList.end(); )
	{
		auto jelly = *it;

		jellyPos = jelly->GetPosition();
		jellyPos.x += dt * jellySpeed*-dir;
		jellyPos.y = 250.f;
		jelly->SetPosition(jellyPos);

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
	if (jellyPos.x < jeyllSpawnTriggerX)
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

	float startJellyX = activeJellyList.empty() ? 300.f : activeJellyList.back()->GetPosition().x + jellys->sprite.getGlobalBounds().width+10.f;
	jellys->SetActive(true);
	jellys->Init();
	jellys->SetPosition({ startJellyX, 300 });
	activeJellyList.push_back(jellys);

	return jellys;
}

void StageManager::SetTile(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float SpawnTriggerX = FRAMEWORK.GetWindowBounds().left - tileWidth;

	for (auto it = activeTiles.begin(); it != activeTiles.end(); )
	{
		auto tile = *it;
		tilePos = tile->GetPosition();
		tilePos.x += dt * playerSpeed * -dir;
		tile->SetPosition({ tilePos.x, tile->GetPosition().y });

		if (tilePos.x < -tileWidth)//------------------------------------tile->SetActive(false)
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
	if (tilePos.x < SpawnTriggerX)
	{
		SetP2(dt, playerSpeed);
	}
}

void StageManager::SetP1(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float SpawnTriggerX = FRAMEWORK.GetWindowBounds().left - tileWidth;
	int jellyCount = 40;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		activeJellyList.push_back(jellys);
	}
	SetTile(dt, playerSpeed);
	SpawnJelly();
	float jellyWidth = jellys->GetSprite().getGlobalBounds().width;

	for (auto it = activeJellyList.begin(); it != activeJellyList.end(); )
	{
		auto jelly = *it;

		jellyPos = jelly->GetPosition();
		jellyPos.x += dt * jellySpeed * -dir;
		jellyPos.y = 250.f;
		jelly->SetPosition(jellyPos);

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
	if (tilePos.x < SpawnTriggerX)
	{
		SetP2(dt, playerSpeed);
	}
}
void StageManager::SetP2(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float SpawnTriggerX = FRAMEWORK.GetWindowBounds().left - tileWidth;
	SetTile(dt, playerSpeed);

	if (tilePos.x < SpawnTriggerX)
	{
		SetP3(dt, playerSpeed);
	}
}
void StageManager::SetP3(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float SpawnTriggerX = FRAMEWORK.GetWindowBounds().left - tileWidth;
	SetTile(dt, playerSpeed);
	if (tilePos.x < SpawnTriggerX)
	{
		SetP4(dt, playerSpeed);
	}
}
void StageManager::SetP4(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float SpawnTriggerX = FRAMEWORK.GetWindowBounds().left - tileWidth;
	SetTile(dt, playerSpeed);
	if (tilePos.x < SpawnTriggerX)
	{
		SetP1(dt, playerSpeed);
	}
}