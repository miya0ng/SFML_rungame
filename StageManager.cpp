#include "stdafx.h"
#include "StageManager.h"

inline StageManager::TilePattern MakeFlat(TileType type, int n)
{
	return [n,type](StageManager& mgr)
		{
			for (int i = 0; i < n; ++i)
				mgr.SpawnTile(type);
		};
}

inline StageManager::TilePattern MakeGap(TileType type, int g)
{
	return [g,type](StageManager& mgr)
		{
			mgr.lastX += mgr.tileW * g;
		};
}

inline StageManager::TilePattern MakeStair(TileType type, int n, float step)
{
	return [type, n, step](StageManager& mgr)
		{
			float y = mgr.baseY;
			for (int i = 0; i < n; ++i)
			{
				auto t = mgr.SpawnTile(type);
				t->SetPosition({ mgr.lastX, y });
				mgr.lastX += mgr.tileW;
				y -= step;
			}
		};
}

std::vector<TimedPattern> patternTimeline =
{
	{ 0.f,   3.f,  MakeFlat(TileType::Ground, 10) },
	{ 3.f,  5.f,  MakeGap(TileType::Ground, 3) },
	{5.f,  10.f,  MakeStair(TileType::Ground, 3, 40.f) },
};

StageManager::StageManager()
{
}

void StageManager::Init()
{
	tileTexture.loadFromFile("img/Objectimg/map1img/platform1.png");
	tileSprite.setTexture(tileTexture);
	tileSprite.setScale(0.7f, 0.7f);
	//SetPattern(MakeFlat(TileType::Ground, 10));
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

	startX = activeTiles.empty() ? 0.f : activeTiles.back()->GetPosition().x + tileSprite.getGlobalBounds().width;

	newTile->SetPosition({ startX, 300 });
	newTile->SetScale({ 0.7f, 0.7f });
	activeTiles.push_back(newTile);

	float tileWidth = tileSprite.getGlobalBounds().width;
	lastX = startX + tileWidth;
	tileW = tileWidth;

	return newTile;
}


void StageManager::Update(float dt, float playerSpeed)
{
	elapsedTime += dt;

	for (const auto& tp : patternTimeline)
	{
		if (elapsedTime >= tp.startTime && elapsedTime < tp.endTime)
		{
			//SetPattern(tp.pattern);
			break;
		}
	}

	MoveTiles(dt, playerSpeed);

	if (NeedNewTiles() && currentPattern)
		currentPattern(*this);
	/*std::cout << "Tile x=" << startX << ", lastX=" << lastX << std::endl;
	std::cout << "Tile y=" << baseY << std::endl;*/
}

void StageManager::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTiles)
		t->Draw(win);
}

void StageManager::MoveTiles(float dt, float playerSpeed)
{
	//--------------------------------default platform spawn-----------------------------------
	float tileWidth = tileSprite.getGlobalBounds().width;
	float tileSpawnTriggerX = FRAMEWORK.GetWindowBounds().width - tileWidth;

	for (auto it = activeTiles.begin(); it != activeTiles.end(); )
	{
		auto tile = *it;
		pos = tile->GetPosition();
		pos.x += dt * playerSpeed * dir;
		tile->SetPosition({ pos.x, baseY });
		if (pos.x < -tileWidth)//-----------------------------------------tile->SetActive(false)
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

	if (lastX < tileSpawnTriggerX)
	{
		//SpawnTile(TileType::Ground);
		for (const auto& tp : patternTimeline)
		{
			std::cout << elapsedTime << std::endl;
			if (elapsedTime >= tp.startTime && elapsedTime < tp.endTime)
			{
				SetPattern(tp.pattern);
				break;
			}
		}
	}
}

bool StageManager::NeedNewTiles() const
{
	float rightEdge = FRAMEWORK.GetWindowBounds().width;
	return lastX < rightEdge;
}

//void StageManager::SpawnPattern(TileType type)
//{
//	switch (type)
//	{
//	case TileType::Ground:       SpawnFlat();      break;
//	case TileType::Gap:			 SpawnGap();       break;
//	case TileType::Floating:     SpawnFloating();  break;
//	}
//}
//
//void StageManager::SpawnFlat()
//{
//	for (int i = 0; i < 5; ++i)
//	SpawnTile(TileType::Ground);
//}
//void StageManager::SpawnGap()
//{
//	SpawnTile(TileType::Ground);
//	lastX += tileWidth * 2;
//}
//
//void StageManager::SpawnStair()
//{
//	float y = 300;
//	for (int step = 0; step < 4; ++step)
//	{
//		SpawnTile(TileType::Ground)->SetPosition({ lastX, y });
//		lastX += tileWidth;
//		y = 100; // 한 칸씩 위로
//	}
//}