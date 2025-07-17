#include "stdafx.h"
#include "StageManager.h"
#include "Jelly.h"

StageManager::StageManager(std::vector<Jelly*>& active, std::vector<Jelly*>& pooled)
	:jellys(nullptr), tiles(nullptr), jellySpeed(200.f), dir(-1.f), activeJellyList(active),
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

	for (auto it : pooledTileList)
		delete it;
	for (auto it : activeTileList)
		delete it;
	pooledTileList.clear();
	activeTileList.clear();
}


void StageManager::Init()
{
	tileTexture.loadFromFile("graphics/platform.png");
	tileSprite.setTexture(tileTexture);
	tileSprite.setScale(0.7f, 0.7f);

	int jellyCount = 40;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellySpawnX = activeJellyList.empty() ? 300.f :
			activeJellyList.back()->GetPosition().x + jellys->sprite.getGlobalBounds().width + 50.f;
		jellys->SetActive(true);
		jellys->Init();
		jellys->SetPosition({ jellySpawnX,  jellySpawnY });
		activeJellyList.push_back(jellys);
	}

	int tileCount = 30;
	for (int i = 0; i < tileCount; ++i)
	{
		tiles = new Platform();
		tileSpawnX = activeTileList.empty() ? 0.f : activeTileList.back()->GetPosition().x + tileSprite.getGlobalBounds().width;
		tiles->SetActive(true);
		tiles->Init();
		tiles->SetPosition({ tileSpawnX,  tileSpawnY });
		//tiles->SetScale({ 0.7f, 0.7f });
		activeTileList.push_back(tiles);
	}
}

void StageManager::Update(float dt, float playerSpeed)
{
	SetP1(dt, playerSpeed);
}

void StageManager::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTileList)
	{
		t->Draw(win);
	}

	for (auto* t : activeJellyList)
	{
		t->Draw(win);
	}
}

void StageManager::SetP1(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float tilePooledTriggerX = FRAMEWORK.GetWindowBounds().left - tileWidth;

	for (auto it = activeTileList.begin(); it != activeTileList.end(); )
	{
		auto tile = *it;
		tilePos = tile->GetPosition();
		tilePos.x += dt * playerSpeed * dir;
		tilePos.y = 300.f;
		tile->SetPosition({ tilePos.x, tile->GetPosition().y });

		if (tilePos.x < -tileWidth)//------------------------------------tile->SetActive(false)
		{
			tile->SetActive(false);
			pooledTileList.push_back(tile);
			it = activeTileList.erase(it);
		}
		else
		{
			++it;
		}
	}
	float jellyWidth = jellys->GetSprite().getGlobalBounds().width;
	float jellyPooledTriggerX = FRAMEWORK.GetWindowBounds().left - jellyWidth;
	for (auto it = activeJellyList.begin(); it != activeJellyList.end(); )
	{
		auto jelly = *it;
		jellyPos = jelly->GetPosition();
		jellyPos.x += dt * jellySpeed * dir;
		jellyPos.y = 250.f;
		jelly->SetPosition(jellyPos);

		if (jellyPos.x < jellyPooledTriggerX)//------------------------------------jelly->SetActive(false)
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

	if (tilePos.x < tilePooledTriggerX )
	{
		std::cout << "next pattern" << std::endl;
		//SetP2(dt, playerSpeed);
	}
}
void StageManager::SetP2(float dt, float playerSpeed)
{
	
}
void StageManager::SetP3(float dt, float playerSpeed)
{

}
void StageManager::SetP4(float dt, float playerSpeed)
{
	
}