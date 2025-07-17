
#include "stdafx.h"
#include "Pattern1.h"
#include "Jelly.h"
#include "Platform.h"
#include "Obstacle.h"

Pattern1::Pattern1()
{

}

Pattern1::~Pattern1()
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

	for (auto it : pooledConeList)
		delete it;
	for (auto it : activeConeList)
		delete it;
	pooledConeList.clear();
	activeConeList.clear();
}

void Pattern1::Init()
{
	tileTexture.loadFromFile("graphics/platform.png");
	tileSprite.setTexture(tileTexture);
	tileSprite.setScale(0.7f, 0.7f);

	float amplitude = -44.f;
	float frequency = 1.5f;
	int jellyCount = 200;
	int archStart = 18;
	int archEnd = 26;
	int archLength = archEnd - archStart;
	int jellyInterval = 5;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		
		jellySpawnX += jellySpacing;
		jellys->SetActive(true);
		jellys->SetOrigin(Origins::MC);
		jellys->Init();

		if (i >= archStart && i <= archEnd)
		{
			float t = static_cast<float>(i - archStart) / archLength; // 0 ~ 1
			float angle = 3.14159265358979323846f * t;
			jellySpawnY += amplitude * std::sin(frequency * (angle));
		}
		if (i >= archStart + jellyInterval && i <= archEnd + jellyInterval)
		{
			float t = static_cast<float>(i - archStart+ jellyInterval) / archLength; // 0 ~ 1
			float angle = 3.14159265358979323846f * t;
			jellySpawnY += amplitude * std::sin(frequency * (angle));
		}

		else jellySpawnY = 220.f;
		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		activeJellyList.push_back(jellys);
	}

	int tileCount = 180;
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
	float spacing = 415.f;
	int coneCount = 10;
	for (int i = 0; i < coneCount; ++i)
	{
		cones = new Obstacle("cone");
		cones->SetActive(true);
		cones->Init();
		cones->SetPosition({ coneSpawnX + i * spacing, coneSpawnY });
		cones->SetOrigin(Origins::BC);

		activeConeList.push_back(cones);
	}
}
void Pattern1::Release()
{

}
void Pattern1::Reset()
{

}
void Pattern1::Update(float dt)
{

}
void Pattern1::Update(float dt, float playerSpeed)
{
	float tileWidth = tileSprite.getGlobalBounds().width;
	float tilePooledTriggerX = FRAMEWORK.GetWindowBounds().width;
	for (auto it = activeTileList.begin(); it != activeTileList.end(); )
	{
		auto tile = *it;
		tilePos = tile->GetPosition();
		tilePos.x += dt * playerSpeed * dir;
		tile->SetPosition({ tilePos.x, tile->GetPosition().y });

		if (tilePos.x < -tileWidth)
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
	//----------------------------------------------------------------------------NextPattern
	if (tilePos.x < tilePooledTriggerX)
	{
		//std::cout << "next pattern" << std::endl;
	}
	//----------------------------------------------------------------------------NextPattern
	float jellyWidth = jellys->GetSprite().getGlobalBounds().width;
	float jellyPooledTriggerX = FRAMEWORK.GetWindowBounds().left - jellyWidth;
	for (auto it = activeJellyList.begin(); it != activeJellyList.end(); )
	{

		auto jelly = *it;
		jellyPos = jelly->GetPosition();
		jellyPos.x += dt * playerSpeed * dir;
		jelly->SetPosition(jellyPos);

		if (jellyPos.x < jellyPooledTriggerX)
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

	float coneWidth = cones->GetSprite().getGlobalBounds().width;
	float conePooledTriggerX = FRAMEWORK.GetWindowBounds().left - coneWidth;
	for (auto it = activeConeList.begin(); it != activeConeList.end(); )
	{
		auto cone = *it;
		conePos = cone->GetPosition();
		conePos.x += dt * playerSpeed * dir;
		cone->SetPosition(conePos);

		if (conePos.x < -coneWidth)
		{
			cone->SetActive(false);
			pooledConeList.push_back(cone);
			it = activeConeList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Pattern1::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTileList)
	{
		t->Draw(win);
	}

	for (auto* t : activeJellyList)
	{
		if (jellys->GetActive())
		{
			t->Draw(win);
		}
	}

	for (auto* t : activeConeList)
	{
		t->Draw(win);
	}
}