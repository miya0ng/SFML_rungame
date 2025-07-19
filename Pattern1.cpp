
#include "stdafx.h"
#include "Pattern1.h"
#include "Jelly.h"
#include "Platform.h"
#include "Obstacle.h"
#include "Coin.h"

Pattern1::Pattern1()
	: tiles(nullptr), aniPlayer(nullptr), jellys(nullptr),
	cones(nullptr), coins(nullptr)
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

	float spacing = 700.f;
	int coneCount = 4;
	for (int i = 0; i < coneCount; ++i)
	{
		cones = new Obstacle("cone");
		cones->SetActive(true);
		cones->Init();
		cones->SetPosition({ coneSpawnX + i * spacing, coneSpawnY });
		cones->SetOrigin(Origins::BC);

		activeConeList.push_back(cones);
	}

	float coinSpacing = 30.f;
	float coinGroupSpacing = 10.f;
	int coinCount = 320;
	int coinArcStart = 50;
	int coinArcEnd = 80;
	int coinArcLength = coinArcEnd - coinArcStart + 1;
	float coinRadius = 80.f;
	float centerX = coinSpawnX + (coinArcStart + coinArcEnd) * 0.5f * coinGroupSpacing;
	float centerY = coinSpawnY;

	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->SetActive(true);
		coins->Init();
		coins->Reset();
		coins->SetType(CoinType::Silver);
		/*if (i >= 50 && i <= 60)
		{
			coins->SetPosition({ coinSpawnX + i * coinGroupSpacing, coinSpawnY - 10.f });
			coins->SetType(CoinType::Gold);
		}
		else if (i >= 60 && i <= 65)
		{
			coins->SetPosition({ coinSpawnX + i * coinGroupSpacing, coinSpawnY - 20.f });
			coins->SetType(CoinType::Silver);
		}
		else if (i >= 65 && i <= 70)
		{
			coins->SetPosition({ coinSpawnX + i * coinGroupSpacing, coinSpawnY - 25.f });
			coins->SetType(CoinType::Silver);
		}
		else if (i >= 70 && i <= 80)
		{
			coins->SetPosition({ coinSpawnX + i * coinGroupSpacing, coinSpawnY - 10.f });
			coins->SetType(CoinType::Gold);
		}*/

		if (i >= coinArcStart && i <= coinArcEnd)
		{
			if (i % 2 == 0)
			{
				pooledCoinList.push_back(coins);
			}
			float t = float(i - coinArcStart) / (coinArcLength - 1);
			float angle = 3.14159265f * t;
			float x = centerX + coinRadius * std::cos(angle);
			float y = centerY - coinRadius * std::sin(angle);

			coins->SetPosition({ x, y });
			if (i % 5 == 0)
				coins->SetType(CoinType::Gold);
			else
				coins->SetType(CoinType::Silver);
		}
		else
		{
			coins->SetPosition({ coinSpawnX + i * coinSpacing, coinSpawnY });
			coins->SetType(CoinType::Silver);
		}
		coins->SetOrigin(Origins::BC);
		activeCoinList.push_back(coins);
	}

	//int jellyCount = 200;
	//int archStart = 8;
	//int archEnd = 16;
	//int archLength = archEnd - archStart;
	//int jellyInterval = 5;
	//int coneIdx = 0;
	//const float jellyradius = 30.f;

	//for (int i = 0; i < jellyCount; ++i)
	//{
	//	jellys = new Jelly();

	//	jellySpawnX += jellySpacing;
	//	jellys->SetActive(true);
	//	jellys->SetOrigin(Origins::MC);
	//	jellys->Init();

	//	while (coneIdx + 1 < activeConeList.size() &&
	//		jellySpawnX > activeConeList[coneIdx]->GetPosition().x + spacing)
	//	{
	//		++coneIdx;
	//	}

	//	if (jellySpawnX > activeConeList[coneIdx]->GetPosition().x &&
	//		jellySpawnX < activeConeList[coneIdx]->GetPosition().x + spacing)
	//	{
	//		float t = float(i - archStart) / (archLength - 1);
	//		float angle = 3.14159265358979323846f * (1.f - t);
	//		jellySpawnY -= jellyradius * std::cos(angle);
	//		jellySpawnY = std::min(jellySpawnY, 220.f);
	//		if (i % 3 == 0)
	//		{
	//			jellys->SetType(JellyType::Yellow);
	//			if (i % 10 == 0 || i % 9 == 0)
	//			{
	//				jellys->SetType(JellyType::Blue);
	//			}
	//		}
	//		if (!activeJellyList.empty() && activeJellyList.back()->GetPosition().y <= 150.f)
	//		{
	//			jellys->SetType(JellyType::Pink);
	//		}
	//	}
	//	else
	//	{
	//		jellySpawnY = 220.f;
	//		jellys->SetType(JellyType::Basic);
	//	}
	//	jellys->SetPosition({ jellySpawnX, jellySpawnY });
	//	activeJellyList.push_back(jellys);
	//}
	jellyQueue.clear();
	jellyQueue.push_back(JellyPattern::Straight);
	jellyQueue.push_back(JellyPattern::Arch);
	jellyQueue.push_back(JellyPattern::Zigzag);

	coinQueue.clear();
	coinQueue.push_back(CoinPattern::Straight);
	coinQueue.push_back(CoinPattern::Arch);
	coinQueue.push_back(CoinPattern::Zigzag);
	currCoinIndex = 0;
	currJellyIndex = 0;

	SpawnNextChunk();
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
	if (!activeJellyList.empty())
	{
		float jellyWidth = activeJellyList.front()->GetSprite()
			.getGlobalBounds().width;

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
			else ++it;
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

		if (conePos.x < -conePooledTriggerX)
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

	//float coneWidth = cones->GetSprite().getGlobalBounds().width;
	float coinPooledTriggerX = FRAMEWORK.GetWindowBounds().left - 50.f;
	for (auto it = activeCoinList.begin(); it != activeCoinList.end(); )
	{
		auto coin = *it;
		coinPos = coin->GetPosition();
		coinPos.x += dt * playerSpeed * dir;
		coin->SetPosition(coinPos);

		if (coinPos.x < coinPooledTriggerX)
		{
			coin->SetActive(false);
			pooledCoinList.push_back(coin);
			it = activeCoinList.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (activeJellyList.empty())
	{
		jellySpawnX = FRAMEWORK.GetWindowBounds().width + 50.f;
		SpawnNextChunk();
	}
}

void Pattern1::Draw(sf::RenderWindow& win)
{
	for (auto* t : activeTileList)
	{
		t->Draw(win);
	}

	//jelly imagefile is not loaded
	for (auto* j : activeJellyList)
	{
		if (jellys->GetActive())
		{
			j->Draw(win);
		}
	}

	for (auto* t : activeConeList)
	{
		t->Draw(win);
	}

	for (auto* t : activeCoinList)
	{
		t->Draw(win);
	}
}
void Pattern1::SpawnStraight()
{
	const int jellyCount = 50;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->Init();
		jellySpawnX += jellySpacing;
		jellySpawnY = 220.f;
		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		jellys->SetType(JellyType::Basic);
		activeJellyList.push_back(jellys);
	}

	const int coinCount = 50;
	float y = 260.f;                            // 타일 위 살짝 높이
	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->Init();
		coinSpawnX += coinSpacing;
		coins->SetPosition({ coinSpawnX, y });
		coins->SetType(CoinType::Silver);
		activeCoinList.push_back(coins);
	}
}

void Pattern1::SpawnArch()
{
	const int jellyCount = 30;
	const float jellyRadius = 30.f;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->Init();
		jellySpawnX += jellySpacing;

		float t = float(i) / (jellyCount - 1);
		float angle = 3.14159265f * (1.f - t);
		jellySpawnY = 220.f - jellyRadius * std::cos(angle);

		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		jellys->SetType(JellyType::Yellow);
		activeJellyList.push_back(jellys);
	}

	const int coinCount = 10;
	const float coinRadius = 5.f;
	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->Init();
		coinSpawnX += coinSpacing;

		float t = float(i) / (coinCount - 1);
		float angle = 3.14159265f * t;          // 반원
		float y = 260.f - coinRadius * std::sin(angle);

		coins->SetPosition({ coinSpawnX, y });
		coins->SetType(i % 5 == 0 ? CoinType::Gold : CoinType::Silver);
		activeCoinList.push_back(coins);
	}
}

void Pattern1::SpawnZigzag()
{
	const int jellyCount = 40;
	for (int i = 0; i < jellyCount; ++i)
	{
		jellys = new Jelly();
		jellys->Init();
		jellySpawnX += jellySpacing;
		jellySpawnY = (i % 2 == 0) ? 200.f : 240.f;

		jellys->SetPosition({ jellySpawnX, jellySpawnY });
		jellys->SetType(JellyType::Blue);
		activeJellyList.push_back(jellys);
	}
}

void Pattern1::SpawnCoinsStraight()
{

}
void Pattern1::SpawnCoinsArch()
{

}
void Pattern1::SpawnCoinsZigzag()
{
	const int coinCount = 40;
	for (int i = 0; i < coinCount; ++i)
	{
		coins = new Coin("coin");
		coins->Init();
		coinSpawnX += coinSpacing;
		float y = (i % 2 == 0) ? 250.f : 290.f;

		coins->SetPosition({ coinSpawnX, y });
		coins->SetType(CoinType::Silver);
		activeCoinList.push_back(coins);
	}
}

void Pattern1::SpawnNextChunk()
{
	if (jellyQueue.empty()) return;

	JellyPattern jp = jellyQueue[currJellyIndex];
	currJellyIndex = (currJellyIndex + 1) % jellyQueue.size();

	CoinPattern  cp = coinQueue[currCoinIndex];
	currCoinIndex = (currCoinIndex + 1) % coinQueue.size();

	switch (jp)
	{
	case JellyPattern::Straight: SpawnStraight(); break;
	case JellyPattern::Arch:     SpawnArch();     break;
	case JellyPattern::Zigzag:   SpawnZigzag();   break;
	}

	switch (cp)
	{
	case CoinPattern::Straight:  SpawnCoinsStraight(); break;
	case CoinPattern::Arch:      SpawnCoinsArch();     break;
	case CoinPattern::Zigzag:    SpawnCoinsZigzag();   break;
	}
	/*todo:tile/coin */
}